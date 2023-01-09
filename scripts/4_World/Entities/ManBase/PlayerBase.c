modded class PlayerBase
{
    ref DModifiersManager DF_ModifiersManager;

    void Init()
	{
        super.Init();

        if( GetGame().IsServer() )
		{
            DF_ModifiersManager = new DModifiersManager(this);
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DF_OnScheduledTick, TICK_FREQUENCY_MILLIS, true);
        }
    };

    void DF_OnScheduledTick()
	{
		if( DF_ModifiersManager ) DF_ModifiersManager.OnScheduledTick();
	};

    override void OnStoreSave( ParamsWriteContext ctx )
	{
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
			DF_ModifiersManager.OnStoreSave(ctx);
        }

        super.OnStoreSave(ctx);
    };

    override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
			if(!DF_ModifiersManager.OnStoreLoad(ctx))
			{
                GetLogger().Error("Failed to load ModifiersManager, read fail.");
				return false;
			}
        }

        return super.OnStoreLoad(ctx,version);
    };
};