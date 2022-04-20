modded class MissionServer
{
    Bootstrap bootstrap;

    void MissionServer()
    {
        bootstrap = new Bootstrap();
        bootstrap.PreInit();
    }
};