[Mod(Bootstrap,"DFramework")]
class Bootstrap extends DayZModification
{
    static Bootstrap INSTANCE;

    void Bootstrap()
    {
        INSTANCE = this;
    };

    override void OnInit()
    {
        DFramework.InitializeLogger();
        DFramework.InitializeConfigManager();
        DFramework.InitializeEventManager();
    };

    override void OnMissionPreInit()
    {
    };

    override void OnMissionInit()
    {
    };

    override void OnMissionPostInit()
    {
    };
};