/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class HandlerList
{
    private ref array<ref RegisteredListener> handlers = NULL;
    private ref map<ref DEventPriority, ref array<ref RegisteredListener>> handlerslots = new map<ref DEventPriority, ref array<ref RegisteredListener>>;
    private static ref array<ref HandlerList> allLists = new array<ref HandlerList>;

    static void BakeAll()
    {
        if (allLists)
        {
            foreach (HandlerList handlerList : allLists)
            {
                handlerList.Bake();
            }
        }
    }

    static void UnregisterAll()
    {
        if (allLists)
        {
            foreach (HandlerList handler : allLists)
            {
                (handler.handlerslots).Set(DEventPriority.LOWEST, new array<ref RegisteredListener>);
                (handler.handlerslots).Set(DEventPriority.LOW, new array<ref RegisteredListener>);
                (handler.handlerslots).Set(DEventPriority.NORMAL, new array<ref RegisteredListener>);
                (handler.handlerslots).Set(DEventPriority.HIGH, new array<ref RegisteredListener>);
                (handler.handlerslots).Set(DEventPriority.HIGHEST, new array<ref RegisteredListener>);
                (handler.handlerslots).Set(DEventPriority.MONITOR, new array<ref RegisteredListener>);

                handler.handlers = NULL;
            }
        }
    }

    static void UnregisterAll(string modName)
    {
        if (allLists)
        {
            foreach (HandlerList handler : allLists)
            {
                handler.Unregister(modName);
            }
        }
    }

    static void UnregisterAll(Listener listener)
    {
        if (allLists)
        {
            foreach (HandlerList handler : allLists)
            {
                handler.Unregister(listener);
            }
        }
    }

    void HandlerList() {
        this.handlerslots.Insert(DEventPriority.LOWEST, new array<ref RegisteredListener>);
        this.handlerslots.Insert(DEventPriority.LOW, new array<ref RegisteredListener>);
        this.handlerslots.Insert(DEventPriority.NORMAL, new array<ref RegisteredListener>);
        this.handlerslots.Insert(DEventPriority.HIGH, new array<ref RegisteredListener>);
        this.handlerslots.Insert(DEventPriority.HIGHEST, new array<ref RegisteredListener>);
        this.handlerslots.Insert(DEventPriority.MONITOR, new array<ref RegisteredListener>);

        if (allLists) {
            allLists.Insert(this);
        }
    }

    void Register(RegisteredListener listener)
    {
        if ((this.handlerslots.Get(listener.GetPriority())).Find(listener) != -1)
        {
            GetDFLogger().Error("This listener is alrady registered to priority " + typename.EnumToString(DEventPriority, listener.GetPriority()));
        }
        else
        {
            this.handlers = NULL;

            (this.handlerslots.Get(listener.GetPriority())).Insert(listener);
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
        (handlerslots.Get(listener.GetPriority())).RemoveItem(listener);

        this.handlers = NULL;
    }

    void Unregister(string modName)
    {
        bool changed = false;

        ref array<array<ref RegisteredListener>> var1 = this.handlerslots.GetValueArray();

        foreach (array<ref RegisteredListener> var2 : var1)
        {
            DEventPriority priority = this.handlerslots.GetKeyByValue(var2);
            foreach (RegisteredListener registeredListener : var2)
            {
                if (registeredListener.GetModName() == modName)
                {
                    (handlerslots.Get(priority)).RemoveItem(registeredListener);
                    changed = true;
                }
            }
        }

        if (changed)
        {
            this.handlers = NULL;
        }
    }

    void Unregister(Listener listener)
    {
        bool changed = false;

        ref array<array<ref RegisteredListener>> var1 = this.handlerslots.GetValueArray();

        foreach (array<ref RegisteredListener> var2 : var1)
        {
            DEventPriority priority = this.handlerslots.GetKeyByValue(var2);
            foreach (RegisteredListener registeredListener : var2)
            {
                if ((registeredListener.GetListener()).ClassName() == listener.ClassName())
                {
                    (handlerslots.Get(priority)).RemoveItem(registeredListener);
                    changed = true;
                }
            }
        }

        if (changed)
        {
            this.handlers = NULL;
        }
    }

    void Bake()
    {
        if (this.handlers == NULL)
        {
            this.handlers = new array<ref RegisteredListener>;

            ref array<array<ref RegisteredListener>> var1 = this.handlerslots.GetValueArray();
            
            foreach (array<ref RegisteredListener> var2 : var1)
            {
                foreach (RegisteredListener list : var2)
                {
                    this.handlers.Insert(list);
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
            _handlers = this.handlers;
        }

        return _handlers;
    }

    static ref array<ref RegisteredListener> GetRegisteredListeners(string modName)
    {
        ref array<ref RegisteredListener> listeners = new array<ref RegisteredListener>;

        if (allLists) {
            foreach (HandlerList handler : allLists)
            {
                ref array<array<ref RegisteredListener>> var1 = (handler.handlerslots).GetValueArray();
                
                foreach (array<ref RegisteredListener> list : var1)
                {
                    foreach (RegisteredListener listener : list)
                    {
                        if (listener.GetModName() == modName)
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

        foreach (HandlerList var2 : allLists)
        {
            var1.Insert(var2);
        }

        return var1;
    }
}