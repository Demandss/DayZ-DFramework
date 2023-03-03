class SQLDataSourceQuery extends IDataSourceQuery
{
    private string m_QueryBody;

    void SQLDataSourceQuery(string sql, SQLDataSourceConnection connection)
    {
        int semicolonIndex = sql.LastIndexOf(";") - 1;

        if (semicolonIndex > 0)
            m_QueryBody = sql.Substring(0,semicolonIndex);
        else
            m_QueryBody = sql;

        m_Connection = connection;
    };

    override void SetOffset(int offset)
    {
        m_QueryBody += " OFFSET " + offset;
    };

    override void SetLimit(int limit)
    {
        m_QueryBody += " LIMIT " + limit;
    };

    override string ExecuteStr(EDataSourceQueryResultType type)
    {
        return (m_Connection.GetRestContext()).POST_now(m_Connection.GetRestRequestBody() + "query","mod=" + m_Connection.GetDataSource().GetModification().GetName() + "&type=" + typename.EnumToString(EDataSourceQueryResultType, type) + "&request=" + m_QueryBody);
    };
};