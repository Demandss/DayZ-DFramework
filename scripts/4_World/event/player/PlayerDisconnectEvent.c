/*
 This code powered by ©Demands.
 at 01/09/2023
 */

class PlayerDisconnectEvent extends PlayerEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();

    void PlayerDisconnectEvent(PlayerBase _player) 
    {
        m_Player = _player;
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