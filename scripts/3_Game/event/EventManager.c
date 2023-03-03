/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class DEventManager
{
    private ref map<ref DayZModification,ref map<ref Listener,ref array<ref DEventListenerFunction>>> m_Handlers = new map<ref DayZModification,ref map<ref Listener,ref array<ref DEventListenerFunction>>>;

    void RegisterHandler(DayZModification modification, DEventListenerFunction function)
    {
        if (!m_Handlers.Contains(modification))
        {
            m_Handlers.Insert(modification, new map<ref Listener,ref array<ref DEventListenerFunction>>);
        }

        if (!(m_Handlers.Get(modification)).Contains(function.GetParent()))
        {
            (m_Handlers.Get(modification)).Insert(function.GetParent(),new array<ref DEventListenerFunction>);
        }

        ((m_Handlers.Get(modification)).Get(function.GetParent())).Insert(function);
    }

    ref map<ref typename, ref array<ref RegisteredListener>> CreateRegisteredListeners(Listener listener, DayZModification modification)
    {
        ref map<ref typename, ref array<ref RegisteredListener>> ret = new map<ref typename, ref array<ref RegisteredListener>>;

        ref array<ref DEventListenerFunction> functions = ((m_Handlers.Get(modification)).Get(listener));

        foreach (DEventListenerFunction function : functions)
        {
            if (!ret.Contains(function.GetEvent()))
            {
                ret.Insert(function.GetEvent(), new array<ref RegisteredListener>);
            }

            (ret.Get(function.GetEvent())).Insert(new RegisteredListener(listener,function.GetDEventPriority(),modification,new DEventExecutor(function.GetName())));
        }

        return ret;
    }

    void RegisterEvents(Listener listener, DayZModification modification)
    {
        ref map<ref typename, ref array<ref RegisteredListener>> entry = CreateRegisteredListeners(listener,modification);

        ref array<typename> entryDEvents = entry.GetKeyArray();

        foreach (typename devent : entryDEvents)
        {
            (this.GetEventListeners(devent.Spawn())).RegisterAll(entry.Get(devent));
        }
    }

    private HandlerList GetEventListeners(DEvent devent)
    {
        HandlerList handler;
        GetGame().GameScript.CallFunctionParams( devent, "GetHandlerList", handler, NULL );
        return handler;
    }

    void CallEvent(DEvent devent)
    {
        if (devent.IsAsynchronous())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(fireEvent,devent);
        }
        else
        {
            this.fireEvent(devent);
        }
    }

    private void fireEvent(DEvent devent)
    {
        HandlerList eventHandlers = devent.GetHandlers();

        ref array<ref RegisteredListener> listeners = eventHandlers.GetRegisteredListeners();

        foreach (RegisteredListener registration : listeners)
        {
            registration.CallEvent(devent);
        }
    }
}