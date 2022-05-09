/*
 This code powered by ©Demands.
 at 5/10/2022
 */

class ConfigManager extends FileConfigurationBase
{
    protected map<string, ref map<string, ref Class>> m_ConfigDataBase = new map<string, ref map<string, ref Class>>;

    void ConfigManager()
    {
        if (!m_ConfigDataBase)
            m_ConfigDataBase = new map<string, ref map<string, ref Class>>;
    };

    /**
     * @brief loads the configuration file into memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     */
    void Load(string fileName)
    {
        
    };

    /**
     * @brief save the data to a file and update it in memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    static void Save(string fileName, notnull Class data)
    {
        
    };

    /**
     * @brief needed to register and/or load configuration files.
     *
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    static void Register(string fileName, notnull Class data)
    {
        SetSubFolder(fileName);
        string path = GetPath();

        if (!m_ConfigDataBase)
            m_ConfigDataBase = new map<string, ref map<string, ref Class>>;

        if (FileExist(path))
        {
            Load(fileName);
            return;
        }
        Save(path,data);
    };

    /**
     * @brief updates data about your configs in memory.
     * 
     * @param data here we pass the initialized class.
     */
    void UpdateData(Class data) 
    {
        string directory = GetDirectory();
        string fileName = GetFileName();
        map<string, ref Class> T;
        if (m_ConfigDataBase.Contains(directory))
        {
            T = m_ConfigDataBase.Get(directory);
            if (T.Contains(fileName))
            {
                T.Set(fileName,data);
            }
            else
            {
                T.Insert(fileName,data);
            }
            m_ConfigDataBase.Set(directory,T);
        }
        else
        {
            T = new map<string, ref Class>(fileName,data);
            m_ConfigDataBase.Insert(directory,T);
        }
    };

    /**
     * @brief allows you to get data from the registered config.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @return Class of the same type as it was when registering the config.
     */
    static Class GetData(string fileName)
    {
        SetSubFolder(fileName);

        if (!m_ConfigDataBase)
            m_ConfigDataBase = new map<string, ref map<string, ref Class>>;

        map<string, ref Class> T = m_ConfigDataBase.Get(GetDirectory());
        
        return T.Get(GetFileName());
    };
};

class JsonConfigManager extends ConfigManager
{
    protected static ref JsonSerializer m_Serializer = new JsonSerializer;

    override void Load(string fileName)
    {
        string file_content;
        string line_content;
        string warning;
        Class data;

        FileHandle handle = OpenFile(fileName, FileMode.READ);
        if ( handle == 0 )
            return;
        
        while ( FGets( handle,  line_content ) >= 0 )
        {
            file_content += line_content;
        }
        
        CloseFile( handle );
        
        if( !m_Serializer )
            m_Serializer = new JsonSerializer;
        
        if( !m_Serializer.ReadFromString( data, file_content, warning ) )
            Logger.Warning( warning );

        UpdateData(data);
    };

    override static void Save(string fileName, notnull Class data)
    {
        SetSubFolder(fileName);
        string path = GetPath();

        string file_content;
        if( !m_Serializer )
            m_Serializer = new JsonSerializer;
        
        m_Serializer.WriteToString( data, true, file_content );
        
        FileHandle handle = OpenFile( path, FileMode.WRITE );
        if ( handle == 0 )
            return;
        
        FPrint( handle, file_content );
        
        CloseFile( handle );
        
        UpdateData(data);
    };
};

class BinaryConfigManager
{
    protected static ref FileSerializer m_Serializer = new FileSerializer;

    override void Load(string fileName)
    {
        Class data;

        if( !m_Serializer )
            m_Serializer = new FileSerializer;

        if (m_Serializer.Open(fileName, FileMode.READ))
		{	
			m_Serializer.Read(data);
			m_Serializer.Close();

            UpdateData(data);
		}
    };

    override static void Save(string fileName, notnull Class data)
    {
        SetSubFolder(fileName);
        string path = GetPath();

        if( !m_Serializer )
            m_Serializer = new FileSerializer;

        if (m_Serializer.Open(path, FileMode.WRITE))
		{
			m_Serializer.Write(data);
        	m_Serializer.Close();
            
            UpdateData(data);
		}
    };
};