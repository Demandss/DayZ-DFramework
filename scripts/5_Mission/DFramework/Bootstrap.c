class Bootstrap
{
    void PreInit()
    {
        DFramework.InitializeLogger();
        DFramework.InitializeConfigManager();
        DFramework.InitializeEventManager();
    };

    void Init()
    {
        
    };

    void PostInit()
    {
    };
};