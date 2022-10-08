/*
 This code powered by ©Demands.
 at 10/05/2022
 */

/* 
Let's call it the cry of the soul..

class ConfigMaker<Class T> extends FileConfigurationBase
{
    void Load(string fileName);

    void Save(string fileName, notnull T data);

    void Register(DString fileName, notnull T data)
    {
        //Code
    };
} 

class JsonConfigMaker<Class T> extends ConfigMaker<T>
{
    protected static ref JsonSerializer m_Serializer = new JsonSerializer;

    override Load(string fileName)
    {
        //Code
    };

    override void Save(string fileName, notnull T data)
    {
        //Code
    };
} 

I don’t know who was responsible for the OOP, but he obviously doesn’t know something
*/

class ConfigMaker extends FileConfigurationBase
{
    void SavingCrutch(string fileName, Class val);
};

class JsonConfigMaker<Class T> extends ConfigMaker
{
    protected static ref JsonSerializer m_Serializer = new JsonSerializer;

    /**
     * @brief loads the configuration file into memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     */
    void Load(string fileName)
    {
        SetSubFolder(fileName);
        DString path = GetPath();

        DString file_content;
        DString line_content;
        DString warning;
        T data;

        FileHandle handle = OpenFile(path, FileMode.READ);
        if ( handle == 0 )
        {
            GetLogger().Error(string.Format("I did not find JsonConfigMaker::Load(%1)",fileName));
            return;
        }
        
        while ( FGets( handle,  line_content ) >= 0 )
        {
            file_content += line_content;
        }
        
        CloseFile( handle );

        if( !m_Serializer )
            m_Serializer = new JsonSerializer;
        
        if( !m_Serializer.ReadFromString( data, file_content, warning ) )
            GetLogger().Warning( warning );

        GetConfigManager().UpdateData(fileName,data);
    };

    /**
     * @brief The person in charge of the OOP I hate you, know this!
     */
    override void SavingCrutch(string fileName, Class val)
    {
        T data;
        Class.CastTo(data,val);

        Save(fileName, data, false);
    }

    /**
     * @brief save the data to a file and update it in memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.json".
     * @param data here we pass the initialized class.
     */
    void Save(string fileName, T data, bool updateData = true)
    {
        SetSubFolder(fileName);
        DString path = GetPath();
        DString file_content;
        if( !m_Serializer )
            m_Serializer = new JsonSerializer;

        m_Serializer.WriteToString( data, true, file_content );

        FileHandle handle = OpenFile( path, FileMode.WRITE );
        if ( handle == 0 )
        {
            GetLogger().Error(string.Format("Something went wrong JsonConfigMaker::Save(%1,%2)",fileName,data));
            return;
        }

        FPrint( handle, file_content );

        CloseFile( handle );

        if (updateData)
        {
            GetConfigManager().UpdateData(fileName,data);
        }
    };

    /**
     * @brief needed to register and/or load configuration files.
     *
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    void Register(string fileName)
    {
        SetSubFolder(fileName);
        string path = GetPath();
        
        GenerateDirectory(path);
        if (FileExist(path))
        {
            Load(fileName);
            return;
        }
        T data;
        Class.CastTo(data,T.Spawn());
        Save(fileName,data);
    };
};

class BinaryConfigMaker<Class T> extends ConfigMaker
{
    protected static ref FileSerializer m_Serializer = new FileSerializer;

    /**
     * @brief loads the configuration file into memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     */
    void Load(string fileName)
    {
        T data;

        if( !m_Serializer )
            m_Serializer = new FileSerializer;

        if (m_Serializer.Open(fileName, FileMode.READ))
		{	
			m_Serializer.Read(data);
			m_Serializer.Close();

            GetConfigManager().UpdateData(fileName,data);
		}
    };

    /**
     * @brief The person in charge of the OOP I hate you, know this!
     */
    override void SavingCrutch(string fileName, Class val)
    {
        T data;
        Class.CastTo(data,val);

        Save(fileName, data, false);
    }

    /**
     * @brief save the data to a file and update it in memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.binary".
     * @param data here we pass the initialized class.
     */
    void Save(string fileName, notnull T data, bool updateData = true)
    {
        SetSubFolder(fileName);
        string path = GetPath();

        if( !m_Serializer )
            m_Serializer = new FileSerializer;

        if (m_Serializer.Open(path, FileMode.WRITE))
		{
			m_Serializer.Write(data);
            m_Serializer.Close();

            if (updateData)
            {
                GetConfigManager().UpdateData(fileName,data);
            }
		}
    };

    /**
     * @brief needed to register and/or load configuration files.
     *
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    void Register(string fileName)
    {
        SetSubFolder(fileName);
        string path = GetPath();
        
        GenerateDirectory(path);
        if (FileExist(path))
        {
            Load(fileName);
            return;
        }
        T data;
        Class.CastTo(data,T.Spawn());
        Save(fileName,data);
    };
};