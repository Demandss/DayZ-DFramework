class DFramework
{
    static void InitializeLogger()
    {
        if (GetLogger().isCancelled()) return;

        GetLogger().Initialize();
        GetLogger().Log(LogLevel.NONE,"***Logger successfully initialized***");
    };

    static void InitializeConfigManager()
    {
    };
};