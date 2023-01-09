modded class PlayerBase
{
    ref DModifiersManager dfModifiersManager;

    void Init()
	{
        super.Init();

        if( GetGame().IsServer() )
		{
            dfModifiersManager = new DModifiersManager(this);
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(dfOnScheduledTick, TICK_FREQUENCY_MILLIS, true);
        }
    };

    void dfOnScheduledTick()
	{
		if( dfModifiersManager ) dfModifiersManager.OnScheduledTick();
	};

    override void OnStoreSave( ParamsWriteContext ctx )
	{
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
			dfModifiersManager.OnStoreSave(ctx);
        }

        super.OnStoreSave(ctx);
    };

    override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
			if(!dfModifiersManager.OnStoreLoad(ctx))
			{
                GetDFLogger().Error("Failed to load ModifiersManager, read fail.");
				return false;
			}
        }

        return super.OnStoreLoad(ctx,version);
    };

    override void OnConnect()
    {
        super.OnConnect();

        string joinMessage = "";

        PlayerJoinEvent joinEvent = new PlayerJoinEvent(this,joinMessage);

        GetDEventManager().CallEvent(joinEvent);

        joinMessage = joinEvent.GetJoinMessage();

        GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>(joinMessage), true, this.GetIdentity());
    }
};