/*
 This code powered by ©Demands.
 at 5/10/2022
 */

ref ConfigManager DF_ConfigManager;

class ConfigManager extends FileConfigurationBase
{
    protected autoptr map<string,ref map<string, Class>> m_ConfigDataBase = new map<string, ref map<string, Class>>;

    void ConfigManager()
    {
        if (!m_ConfigDataBase)
            m_ConfigDataBase = new map<string,ref map<string, Class>>;
    };

    /**
     * @brief updates data about your configs in memory.
     * 
     * @param data here we pass the initialized class.
     */
    void UpdateData(string fileName, notnull Class data) 
    {
        SetSubFolder(fileName);

        string directory = GetDirectory();
        string _fileName = GetFileName();
        ref map<string, Class> T;
        
        if (m_ConfigDataBase.Find(directory,T))
        {
            if (T.Contains(_fileName))
            {
                T.Set(_fileName,data);
            }
            else
            {
                T.Insert(_fileName,data);
            }
            m_ConfigDataBase.Set(directory,T);
        }
        else
        {
            T = new map<string, Class>;
            T.Insert(_fileName,data);
            m_ConfigDataBase.Insert(directory,T);
        }
    };

    /**
     * @brief allows you to get data from the registered config.
     * 
     * @code
     *      TestConfigData cfg = TestConfigData.Cast(GetConfigManager().GetData("test/config.json"));
     *      Print(cfg.GetText()); -> I can't even imagine what should be here
     * @endcode
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @return Class of the same type as it was when registering the config.
     */    
    Class GetData(string fileName)
    {
        ref map<string, Class> _ConfigData = new map<string, Class>;

        SetSubFolder(fileName);

        if (!m_ConfigDataBase)
            m_ConfigDataBase = new map<string,ref map<string, Class>>;

        m_ConfigDataBase.Find(GetDirectory(),_ConfigData);
        
        if (!_ConfigData)
        {
            GetLogger().Error(string.Format("I did not find ConfigManager::GetData(%1)",fileName));
            return NULL;
        }

        return _ConfigData.Get(GetFileName());
    };
};

ConfigManager GetConfigManager()
{
    if (!DF_ConfigManager) DF_ConfigManager = new ConfigManager;
    return DF_ConfigManager;
};