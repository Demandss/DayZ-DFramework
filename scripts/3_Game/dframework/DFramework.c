class DFramework
{
    private static ref ModificationManager m_ModificationManager;
    private static ref DEventManager m_DEventManager;

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

    static Bootstrap Get() { return Bootstrap.INSTANCE; };

    static ref ModificationManager GetModificationManager()
    {
        if (!m_ModificationManager) 
            m_ModificationManager = new ModificationManager();

        return m_ModificationManager;
    };

    static ref DEventManager GetDEventManager()
    {
        if ( !m_DEventManager )
            m_DEventManager = new DEventManager();

        return m_DEventManager;
    };
};