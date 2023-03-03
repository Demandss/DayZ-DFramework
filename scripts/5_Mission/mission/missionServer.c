modded class MissionServer
{
    private ref array<ref Modification> m_Modifications;

    void MissionServer()
    {
		DFramework.GetModificationManager().LoadModificationsDescriptionData(); //Temporarily it will be here

        m_Modifications = DFramework.GetModificationManager().GetModifications();

        if (m_Modifications)
            foreach (Modification modification : m_Modifications)
                if (modification != NULL)
                    modification.OnMissionPreInit();
    };

    override void OnInit()
	{
		super.OnInit();

        GetDRPCManager().Register(DFramework.Get(),"ChatMessageHander",this);

        if (m_Modifications)
            foreach (Modification modification : m_Modifications)
                if (modification != NULL)
                    modification.OnMissionInit();
    };

    override void OnMissionStart()
	{
		super.OnMissionStart();
		
        if (m_Modifications)
            foreach (Modification modification : m_Modifications)
                if (modification != NULL)
                    modification.OnMissionPostInit();
    };

    void ChatMessageHander(DRPCType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param2<PlayerBase,string> data;
        if ( !ctx.Read( data ) ) return;

        ref set<PlayerBase> recipients = new set<PlayerBase>;

        foreach(Man player : m_Players)
        {
            recipients.Insert(PlayerBase.Cast(player));
        }

        PlayerChatEvent devent = new PlayerChatEvent(data.param1,data.param2,recipients);

        DFramework.GetDEventManager().CallEvent(devent);

        if (!devent.GetRecipients() || devent.GetRecipients().Count() < 1) return;

        foreach(PlayerBase p : devent.GetRecipients())
        {
            string msg = string.Format(devent.GetFormat(),devent.GetPlayer().GetIdentity().GetName(),devent.GetMessage());
			GetGame().ChatMP(p, msg, "0xFFFFFFFF");
        }
    };
};