modded class AnalyticsManagerServer
{
    override void OnEntityKilled( Object killer, EntityAI target )
	{
        DFramework.GetDEventManager().CallEvent(new EntityKilledEvent(target,killer));
		super.OnEntityKilled(killer,target);
	};

    override void OnEntityHit( EntityAI source, Man target )
	{
        DFramework.GetDEventManager().CallEvent(new EntityHitedEvent(target,source));
		super.OnEntityHit(source,target);
    };
};