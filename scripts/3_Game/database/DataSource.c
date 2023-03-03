class DataSource extends IDataSource
{
    private string m_Type = "sqlite";
    private string m_FileName = "database";
    private bool m_IsSQL = true;
    private string m_RestUrl = "localhost:8080";
    private string m_Host = "localhost";
    private string m_Username = "root";
    private string m_Password = "root";
    private DayZModification m_Modification;

    void SetType(EDataSourceType type)
    {
        m_Type = typename.EnumToString(EDataSourceType, type);
    };

    EDataSourceType GetType01()
    {
        return typename.StringToEnum(EDataSourceType, m_Type);
    };

    string GetType02()
    {
        return m_Type;
    };

    string GetFileName()
    {
        return m_FileName;
    };
    
    void SetFileName(string fileName)
    {
        m_FileName = fileName;
    };

    /* void SetIsSQL(bool state)
    {
        m_IsSQL = state; //Appear with NoSQLDataSourceConnection
    }; */

    bool IsSQL()
    {
        return m_IsSQL;
    };

    void SetRestUrl(string url)
    {
        if (url != string.Empty)
            m_RestUrl = url.Trim();
        else
            m_RestUrl = string.Empty;
    };

    string GetRestUrl()
    {
        return m_RestUrl;
    };

    void SetHost(string host)
    {
        if (host != string.Empty)
            m_Host = host.Trim();
        else
            m_Host = string.Empty;
    };

    string GetHost()
    {
        return m_Host;
    };

    void SetUsername(string username)
    {
        m_Username = username;
    };

    string GetUsername()
    {
        return m_Username;
    };

    void SetPassword(string password)
    {
        m_Password = password;
    };

    string GetPassword()
    {
        return m_Password;
    };

    DayZModification GetModification()
    {
        return m_Modification;
    };

    void DataSource(DayZModification modification)
    {
        m_Modification = modification;
    };

    override DataSourceConnection GetConnection()
    {
        if (IsSQL())
            return SQLDataSourceConnection(this);
        else
            return NULL; //TODO - Make NoSQLDataSourceConnection
    };
};