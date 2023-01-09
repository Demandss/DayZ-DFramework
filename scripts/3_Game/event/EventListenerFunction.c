/*
 This code powered by ©Demands.
 at 12/09/2023
 */

class DEventListenerFunction extends Function
{
    protected typename devent;
    protected DEventPriority priority;

    void DEventListenerFunction(string _name, Class _parent, typename _devent, DEventPriority _priority = DEventPriority.NORMAL)
    {
        name = _name;
        parent = _parent;
        this.devent = _devent;
        this.priority = _priority;
    }

    typename GetEvent() { return this.devent; };

    DEventPriority GetDEventPriority() { return this.priority; };
}