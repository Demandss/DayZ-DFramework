modded class MissionServer
{
    ref Bootstrap bootstrap;

    void MissionServer()
    {
        bootstrap = new Bootstrap();
        bootstrap.PreInit();
    }
};