/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class DEventManager
{
    private ref map<string,ref map<ref Listener,ref array<ref DEventListenerFunction>>> handlers = new map<string,ref map<ref Listener,ref array<ref DEventListenerFunction>>>;

    void RegisterHandler(string modName, DEventListenerFunction function)
    {
        if (!handlers.Contains(modName))
        {
            handlers.Insert(modName, new map<ref Listener,ref array<ref DEventListenerFunction>>);
        }

        if (!(handlers.Get(modName)).Contains(function.GetParent()))
        {
            (handlers.Get(modName)).Insert(function.GetParent(),new array<ref DEventListenerFunction>);
        }

        ((handlers.Get(modName)).Get(function.GetParent())).Insert(function);
    }

    ref map<ref typename, ref array<ref RegisteredListener>> CreateRegisteredListeners(Listener listener, string modName)
    {
        ref map<ref typename, ref array<ref RegisteredListener>> ret = new map<ref typename, ref array<ref RegisteredListener>>;

        ref array<ref DEventListenerFunction> functions = ((handlers.Get(modName)).Get(listener));

        foreach (DEventListenerFunction function : functions)
        {
            if (!ret.Contains(function.GetEvent()))
            {
                ret.Insert(function.GetEvent(), new array<ref RegisteredListener>);
            }

            (ret.Get(function.GetEvent())).Insert(new RegisteredListener(listener,function.GetDEventPriority(),modName,new DEventExecutor(function.GetName())));
        }

        return ret;
    }

    void RegisterEvents(Listener listener, string modName)
    {
        ref map<ref typename, ref array<ref RegisteredListener>> entry = CreateRegisteredListeners(listener,modName);

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

static ref DEventManager g_DEventManager;

static DEventManager GetDEventManager()
{
	if ( !g_DEventManager )
		g_DEventManager = new DEventManager();

	return g_DEventManager;
}