class EntityHitedEvent extends DEntityEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();
    protected EntityAI m_Source;

    void EntityHitedEvent(EntityAI _entity, EntityAI _source)
    {
        m_Entity = _entity;
        this.m_Source = _source;
    };

    EntityAI GetHitSource()
    {
        return this.m_Source;
    };

    override ref HandlerList GetHandlers() 
    {
        return m_Handlers;
    };

    override static ref HandlerList GetHandlerList() 
    {
        return m_Handlers;
    };
}