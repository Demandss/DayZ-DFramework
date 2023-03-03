/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class PlayerConnectEvent extends PlayerEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();
    protected string m_JoinMessage;
    protected string m_MessageColor;

    void PlayerConnectEvent(PlayerBase _player, string _joinMessage) 
    {
        m_Player = _player;
        this.m_JoinMessage = _joinMessage;
        this.m_MessageColor = "colorAction";
    };

    string GetJoinMessage() 
    {
        return this.m_JoinMessage;
    };

    string GetJoinMessageColor() 
    {
        return this.m_MessageColor;
    };

    void SetJoinMessage(string _joinMessage, string _color = "colorAction") 
    {
        this.m_JoinMessage = _joinMessage;
        this.m_MessageColor = _color;
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