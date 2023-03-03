class EntityKilledEvent extends DEntityEvent
{
    protected static ref HandlerList handlers = new HandlerList();
    protected Object m_Killer;

    void EntityKilledEvent(EntityAI _entity, Object _killer)
    {
        m_Entity = _entity;
        this.m_Killer = _killer;
    };

    Object GetKiller()
    {
        return this.m_Killer;
    };

    overrideref HandlerList GetHandlers() 
    {
        return handlers;
    };

    override static ref HandlerList GetHandlerList() 
    {
        return handlers;
    };
}