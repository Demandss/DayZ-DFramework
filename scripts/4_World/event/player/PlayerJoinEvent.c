/*
 This code powered by ©Demands.
 at 12/30/2023
 */

class PlayerJoinEvent extends PlayerEvent
{
    private static ref HandlerList handlers = new HandlerList();
    private string joinMessage;

    void PlayerJoinEvent(PlayerBase playerJoined, string _joinMessage) 
    {
        player = playerJoined;
        this.joinMessage = _joinMessage;
    };

    string GetJoinMessage() 
    {
        return this.joinMessage;
    };

    void SetJoinMessage(string _joinMessage) 
    {
        this.joinMessage = _joinMessage;
    };

    ref HandlerList GetHandlers() 
    {
        return handlers;
    };

    static ref HandlerList GetHandlerList() 
    {
        return handlers;
    };
}