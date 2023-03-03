/*
 This code powered by ©Demands.
 at 12/09/2023
 */

class DEventListenerFunction extends Function
{
    protected typename m_DEvent;
    protected DEventPriority m_Priority;

    void DEventListenerFunction(string _name, Class _parent, typename _devent, DEventPriority _priority = DEventPriority.NORMAL)
    {
        name = _name;
        parent = _parent;
        this.m_DEvent = _devent;
        this.m_Priority = _priority;
    }

    typename GetEvent() { return this.m_DEvent; };

    DEventPriority GetDEventPriority() { return this.m_Priority; };
}