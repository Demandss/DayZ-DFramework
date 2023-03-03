/*
 This code powered by ©Demands.
 at 10/23/2022
 */

enum DEventResult {
    DENY,
    DEFAULT,
    ALLOW
};

class DEvent
{
    protected string m_Name = string.Empty;
    protected bool m_IsAsync;

    void DEvent() 
    {
        this.m_IsAsync = false;
    };

    string GetEventName() 
    {
        if (m_Name == string.Empty) 
        {
            m_Name = this.ClassName();
        }
        return m_Name;
    };

    ref HandlerList GetHandlers();

    static ref HandlerList GetHandlerList();

    bool IsAsynchronous() 
    {
        return m_IsAsync;
    };
};