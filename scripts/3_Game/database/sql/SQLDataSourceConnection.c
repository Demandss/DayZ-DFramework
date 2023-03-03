class SQLDataSourceConnection extends DataSourceConnection
{
    void SQLDataSourceConnection(DataSource source)
    {
        m_DataSource = source;
        m_RestRequestBody = "/api/database/sql/";

        if (!GetRestApi())
		{
			CreateRestApi();
		}

        m_CurlContext = GetRestApi().GetRestContext(m_DataSource.GetRestUrl());
        m_CurlContext.SetHeader("application/x-www-form-urlencoded");
        string response = m_CurlContext.POST_now(m_RestRequestBody + "connect",string.Format("mod=%1&type=%2&file=%3&host=%4&user=%5&password=%6", m_DataSource.GetModification().GetName(), m_DataSource.GetType02(), m_DataSource.GetFileName(), m_DataSource.GetHost(), m_DataSource.GetUsername(), m_DataSource.GetPassword()));
    
        GetDFLogger().Info("Connecting "+m_DataSource.GetModification().GetName()+" to database :: " + response);
    };

    /**
     * @brief Executes the given SQL statement, which may be an INSERT, UPDATE, or DELETE statement 
     *        or an SQL statement that returns nothing, such as an SQL DDL statement.
     * 
     * @param sql – an SQL Data Manipulation Language (DML) statement, such as INSERT, UPDATE or DELETE; or an SQL statement that returns nothing, such as a DDL statement.
     * @return true if everything worked out or false if some error occurred, see the error in the DFrameworkBridge console
     */
    bool ExecuteUpdate(string sql)
    {
        string response = m_CurlContext.POST_now(m_RestRequestBody + "update","mod=" + m_DataSource.GetModification().GetName() + "&request=" + sql);

        return response == "Success";
    };

    IDataSourceQuery CreateQuery(string sql)
    {
        return new SQLDataSourceQuery(sql,this);
    };

    void Close()
    {
        m_CurlContext.POST_now(m_RestRequestBody + "disconnect","mod=" + m_DataSource.GetModification().GetName());
    };
};