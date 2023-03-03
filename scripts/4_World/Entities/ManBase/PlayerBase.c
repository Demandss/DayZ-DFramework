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

        PlayerConnectEvent joinEvent = new PlayerConnectEvent(this,joinMessage);

        DFramework.GetDEventManager().CallEvent(joinEvent);

        joinMessage = joinEvent.GetJoinMessage();
        string joinMessageColor = joinEvent.GetJoinMessageColor();

        Message(joinMessage,joinMessageColor);
    };

    override void OnDisconnect()
    {
        DFramework.GetDEventManager().CallEvent(new PlayerDisconnectEvent(this));
        super.OnDisconnect();
    };

    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
        DFramework.GetDEventManager().CallEvent(new PlayerHitedEvent(this, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef));
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    };

	override void EEKilled( Object killer )
	{
        DFramework.GetDEventManager().CallEvent(new PlayerKilledEvent(this,killer));
		super.EEKilled( killer );
    };
};