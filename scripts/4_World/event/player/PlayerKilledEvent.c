class PlayerKilledEvent extends PlayerEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();
    protected Object m_Killer;

    void PlayerKilledEvent(PlayerBase _player, Object _killer)
    {
        m_Player = _player;
        this.m_Killer = _killer;
    };

    Object GetKiller()
    {
        return this.m_Killer;
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