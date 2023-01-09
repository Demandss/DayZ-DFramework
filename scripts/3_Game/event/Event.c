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
    protected string name = string.Empty;
    protected bool async;

    void DEvent() 
    {
        this.async = false;
    };

    string GetEventName() 
    {
        if (name == string.Empty) 
        {
            name = this.ClassName();
        }
        return name;
    };

    ref HandlerList GetHandlers();

    static ref HandlerList GetHandlerList();

    bool IsAsynchronous() 
    {
        return async;
    };
};