class DFramework
{
    static void InitializeLogger()
    {
        if (GetDFLogger().isCancelled()) return;

        GetDFLogger().Initialize();
        GetDFLogger().Log(LogLevel.NONE,"***Logger successfully initialized***");
    };

    static void InitializeConfigManager()
    {
        GetConfigManager();
    };

    static void InitializeEventManager()
    {
        GetDEventManager();
    };
};