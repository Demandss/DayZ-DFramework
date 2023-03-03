class IDataSourceQuery
{
    protected DataSourceConnection m_Connection;

    void SetOffset(int offset);

    void SetLimit(int limit);

    ref DataSourceQueryResult Execute()
    {
        return new DataSourceQueryResult(ExecuteStr(EDataSourceQueryResultType.json));
    };

    string ExecuteStr(EDataSourceQueryResultType type);
};