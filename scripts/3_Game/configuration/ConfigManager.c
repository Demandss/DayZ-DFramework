/*
 This code powered by ©Demands.
 at 5/10/2022
 */

ref ConfigManager dfConfigManager;

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
     */
    void UpdateData(string fileName, notnull Class data, ConfigMaker cfgMaker = NULL) 
    {
        SetSubFolder(fileName);

        string directory = GetDirectory();
        string _fileName = GetFileName();
        ref map<string, Class> arr;

        if (m_ConfigDataBase.Find(directory,arr))
        {
            if (arr.Contains(_fileName))
            {
                arr.Set(_fileName,data);
            }
            else
            {
                arr.Insert(_fileName,data);
            }
            m_ConfigDataBase.Set(directory,arr);
        }
        else
        {
            arr = new map<string, Class>;
            arr.Insert(_fileName,data);
            m_ConfigDataBase.Insert(directory,arr);
        }

        if (cfgMaker)
            SetFileData(fileName,data,cfgMaker);
    };

    void SetFileData(string fileName, notnull Class data, ConfigMaker cfgMaker)
    {
        cfgMaker.SavingCrutch(fileName,data);
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
            GetDFLogger().Error(string.Format("I did not find ConfigManager::GetData(%1)",fileName));
            return NULL;
        }

        return _ConfigData.Get(GetFileName());
    };
};

ConfigManager GetConfigManager()
{
    if (!dfConfigManager) dfConfigManager = new ConfigManager;
    return dfConfigManager;
};