class IDataSourceQuery
{
    protected DataSourceConnection m_Connection;

    ref DataSourceQueryResult ExecuteNow()
    {
        return new DataSourceQueryResult(ExecuteStrNow(EDataSourceQueryResultType.json));
    };

    void Execute(Class inst, string function);

    string ExecuteStrNow(EDataSourceQueryResultType type);

    string ExecuteStr(EDataSourceQueryResultType type);

    void ExecuteCallBack(EDataSourceQueryResultType type, ref DataBaseCallback callBack);
};