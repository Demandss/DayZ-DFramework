/*
 This code powered by ©Demands.
 at 10/05/2022
 */

/* 
Let's call it the cry of the soul..

class ConfigMaker<Class T> extends FileConfigurationBase
{
    proto void Load(DString filename);

    proto void Save(DString filename, notnull T data);

    void Register(DString fileName, notnull T data)
    {
        //Code
    };
} 

class JsonConfigMaker<Class T> extends ConfigMaker<T>
{
    protected static ref JsonSerializer m_Serializer = new JsonSerializer;

    override Load(DString filename)
    {
        //Code
    };

    override void Save(DString fileName, notnull T data)
    {
        //Code
    };
} 

I don’t know who was responsible for the OOP, but he obviously doesn’t know something
*/

class JsonConfigMaker<Class T> extends FileConfigurationBase
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
     * @brief save the data to a file and update it in memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    void Save(string fileName, T data)
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

        GetConfigManager().UpdateData(fileName,data);
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
        Save(fileName,T.Spawn());
    };
};

class BinaryConfigMaker<Class T> extends FileConfigurationBase
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
     * @brief save the data to a file and update it in memory.
     * 
     * @param fileName is a path to a file like "/folder/filename.cfg".
     * @param data here we pass the initialized class.
     */
    void Save(string fileName, notnull T data)
    {
        SetSubFolder(fileName);
        string path = GetPath();

        if( !m_Serializer )
            m_Serializer = new FileSerializer;

        if (m_Serializer.Open(path, FileMode.WRITE))
		{
			m_Serializer.Write(data);
            m_Serializer.Close();

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
        Save(fileName,T.Spawn());
    };
};