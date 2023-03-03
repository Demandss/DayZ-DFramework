/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class HandlerList
{
    private ref array<ref RegisteredListener> m_Handlers = NULL;
    private ref map<ref DEventPriority, ref array<ref RegisteredListener>> m_Handlerslots = new map<ref DEventPriority, ref array<ref RegisteredListener>>;
    private static ref array<ref HandlerList> m_AllLists = new array<ref HandlerList>;

    static void BakeAll()
    {
        if (m_AllLists)
        {
            foreach (HandlerList handlerList : m_AllLists)
            {
                handlerList.Bake();
            }
        }
    }

    static void UnregisterAll()
    {
        if (m_AllLists)
        {
            foreach (HandlerList handler : m_AllLists)
            {
                (handler.m_Handlerslots).Set(DEventPriority.LOWEST, new array<ref RegisteredListener>);
                (handler.m_Handlerslots).Set(DEventPriority.LOW, new array<ref RegisteredListener>);
                (handler.m_Handlerslots).Set(DEventPriority.NORMAL, new array<ref RegisteredListener>);
                (handler.m_Handlerslots).Set(DEventPriority.HIGH, new array<ref RegisteredListener>);
                (handler.m_Handlerslots).Set(DEventPriority.HIGHEST, new array<ref RegisteredListener>);
                (handler.m_Handlerslots).Set(DEventPriority.MONITOR, new array<ref RegisteredListener>);

                handler.m_Handlers = NULL;
            }
        }
    }

    static void UnregisterAll(DayZModification modification)
    {
        if (m_AllLists)
        {
            foreach (HandlerList handler : m_AllLists)
            {
                handler.Unregister(modification);
            }
        }
    }

    static void UnregisterAll(Listener listener)
    {
        if (m_AllLists)
        {
            foreach (HandlerList handler : m_AllLists)
            {
                handler.Unregister(listener);
            }
        }
    }

    void HandlerList() {
        this.m_Handlerslots.Insert(DEventPriority.LOWEST, new array<ref RegisteredListener>);
        this.m_Handlerslots.Insert(DEventPriority.LOW, new array<ref RegisteredListener>);
        this.m_Handlerslots.Insert(DEventPriority.NORMAL, new array<ref RegisteredListener>);
        this.m_Handlerslots.Insert(DEventPriority.HIGH, new array<ref RegisteredListener>);
        this.m_Handlerslots.Insert(DEventPriority.HIGHEST, new array<ref RegisteredListener>);
        this.m_Handlerslots.Insert(DEventPriority.MONITOR, new array<ref RegisteredListener>);

        if (m_AllLists) {
            m_AllLists.Insert(this);
        }
    }

    void Register(RegisteredListener listener)
    {
        if ((this.m_Handlerslots.Get(listener.GetPriority())).Find(listener) != -1)
        {
            GetDFLogger().Error("This listener is alrady registered to priority " + typename.EnumToString(DEventPriority, listener.GetPriority()));
        }
        else
        {
            this.m_Handlers = NULL;

            (this.m_Handlerslots.Get(listener.GetPriority())).Insert(listener);
        }
    }

    void RegisterAll(array<ref RegisteredListener> listeners)
    {
        if (listeners)
        {
            foreach (RegisteredListener listener : listeners)
            {
                this.Register(listener);
            }
        }
    }

    void Unregister(RegisteredListener listener)
    {
        (m_Handlerslots.Get(listener.GetPriority())).RemoveItem(listener);

        this.m_Handlers = NULL;
    }

    void Unregister(DayZModification modification)
    {
        bool changed = false;

        ref array<array<ref RegisteredListener>> var1 = this.m_Handlerslots.GetValueArray();

        foreach (array<ref RegisteredListener> var2 : var1)
        {
            DEventPriority priority = this.m_Handlerslots.GetKeyByValue(var2);
            foreach (RegisteredListener registeredListener : var2)
            {
                if (registeredListener.GetModification() == modification)
                {
                    (m_Handlerslots.Get(priority)).RemoveItem(registeredListener);
                    changed = true;
                }
            }
        }

        if (changed)
        {
            this.m_Handlers = NULL;
        }
    }

    void Unregister(Listener listener)
    {
        bool changed = false;

        ref array<array<ref RegisteredListener>> var1 = this.m_Handlerslots.GetValueArray();

        foreach (array<ref RegisteredListener> var2 : var1)
        {
            DEventPriority priority = this.m_Handlerslots.GetKeyByValue(var2);
            foreach (RegisteredListener registeredListener : var2)
            {
                if ((registeredListener.GetListener()).ClassName() == listener.ClassName())
                {
                    (m_Handlerslots.Get(priority)).RemoveItem(registeredListener);
                    changed = true;
                }
            }
        }

        if (changed)
        {
            this.m_Handlers = NULL;
        }
    }

    void Bake()
    {
        if (this.m_Handlers == NULL)
        {
            this.m_Handlers = new array<ref RegisteredListener>;

            ref array<array<ref RegisteredListener>> var1 = this.m_Handlerslots.GetValueArray();
            
            foreach (array<ref RegisteredListener> var2 : var1)
            {
                foreach (RegisteredListener list : var2)
                {
                    this.m_Handlers.Insert(list);
                }
            }
        }
    }

    ref array<ref RegisteredListener> GetRegisteredListeners()
    {
        ref array<ref RegisteredListener> _handlers;
        while(_handlers == NULL)
        {
            this.Bake();
            _handlers = this.m_Handlers;
        }

        return _handlers;
    }

    static ref array<ref RegisteredListener> GetRegisteredListeners(DayZModification modification)
    {
        ref array<ref RegisteredListener> listeners = new array<ref RegisteredListener>;

        if (m_AllLists) {
            foreach (HandlerList handler : m_AllLists)
            {
                ref array<array<ref RegisteredListener>> var1 = (handler.m_Handlerslots).GetValueArray();
                
                foreach (array<ref RegisteredListener> list : var1)
                {
                    foreach (RegisteredListener listener : list)
                    {
                        if (listener.GetModification() == modification)
                        {
                            listeners.Insert(listener);
                        }
                    }                    
                }
            }
        }

        return listeners;
    }

    static array<ref HandlerList> GetHandlerList()
    {
        ref array<ref HandlerList> var1 = new array<ref HandlerList>;

        foreach (HandlerList var2 : m_AllLists)
        {
            var1.Insert(var2);
        }

        return var1;
    }
}