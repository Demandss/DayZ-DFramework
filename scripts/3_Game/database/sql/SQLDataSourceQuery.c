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

    override string ExecuteStrNow(EDataSourceQueryResultType type)
    {
        return (m_Connection.GetRestContext()).POST_now(m_Connection.GetRestRequestBody() + "query","mod=" + m_Connection.GetDataSource().GetModification().GetName() + "&type=" + typename.EnumToString(EDataSourceQueryResultType, type) + "&request=" + m_QueryBody);
    };

    override void Execute(Class inst, string function)
    {
		ref DataBaseCallback callBack = new DataBaseCallback();
        callBack.SetResultSendMethod(inst,function);

        ExecuteCallBack(EDataSourceQueryResultType.json,callBack);
    };

    override void ExecuteCallBack(EDataSourceQueryResultType type,ref DataBaseCallback callBack)
    {
        callBack.SetRequest(m_QueryBody);
        RestContext context = m_Connection.GetRestContext();
        string requestBody = m_Connection.GetRestRequestBody();
        string modificationName = m_Connection.GetDataSource().GetModification().GetName();
        string resultType = typename.EnumToString(EDataSourceQueryResultType, type);
        context.POST(callBack,requestBody + "query","mod=" + modificationName + "&type=" + resultType + "&request=" + m_QueryBody);
    };
};