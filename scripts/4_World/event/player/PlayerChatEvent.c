class PlayerChatEvent extends PlayerEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();
    protected string m_Message;
    protected string m_Format = "%1: %2";
    protected set<PlayerBase> m_Recipients;

    void PlayerChatEvent(PlayerBase who, string _message, set<PlayerBase> _recipients)
    {
        m_Player = who;
        this.m_Message = _message;
        this.m_Recipients = _recipients;
    };

    string GetMessage()
    {
        return this.m_Message;
    };

    void SetMessage(string _message)
    {
        this.m_Message = _message;
    };

    string GetFormat()
    {
        return this.m_Format;
    };

    void SetFormat(string _format)
    {
        if (_format.Contains("%1") && _format.Contains("%2"))
            this.m_Format = _format;
    }

    set<PlayerBase> GetRecipients()
    {
        return this.m_Recipients;
    };

    override ref HandlerList GetHandlers() 
    {
        return m_Handlers;
    };

    override static ref HandlerList GetHandlerList() 
    {
        return m_Handlers;
    };
};