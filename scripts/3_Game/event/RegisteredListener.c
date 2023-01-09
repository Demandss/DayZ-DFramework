/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class RegisteredListener
{
    private ref Listener listener;
    private DEventPriority priority;
    private string modName;
    private ref DEventExecutor executor;

    void RegisteredListener(Listener _listener, DEventPriority _priority, string _modName, DEventExecutor _executor)
    {
        this.listener = _listener;
        this.priority = _priority;
        this.modName = _modName;
        this.executor = _executor;
    };

    Listener GetListener() { return this.listener; };

    string GetModName() { return this.modName; };

    DEventPriority GetPriority() { return this.priority; };

    void CallEvent(DEvent devent)
    {
        executor.Execute(this.listener,devent);
    }
}