modded class MissionServer
{
    ref Bootstrap bootstrap;

    void MissionServer()
    {
        bootstrap = new Bootstrap();

        if (bootstrap)
            bootstrap.PreInit();
    };

    override void OnInit()
	{
		super.OnInit();

        if (bootstrap)
            bootstrap.Init();
    };

    override void OnMissionStart()
	{
		super.OnMissionStart();
		
        if (bootstrap)
            bootstrap.PostInit();
    };
};