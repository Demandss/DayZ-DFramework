/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class RegisteredListener
{
    private ref Listener m_Listener;
    private DEventPriority m_Priority;
    private ref DayZModification m_Modification;
    private ref DEventExecutor m_Executor;

    void RegisteredListener(Listener listener, DEventPriority priority, DayZModification modification, DEventExecutor executor)
    {
        this.m_Listener = listener;
        this.m_Priority = priority;
        this.m_Modification = modification;
        this.m_Executor = executor;
    };

    Listener GetListener() { return this.m_Listener; };

    DayZModification GetModification() { return this.m_Modification; };

    DEventPriority GetPriority() { return this.m_Priority; };

    void CallEvent(DEvent devent)
    {
        m_Executor.Execute(this.m_Listener,devent);
    }
}