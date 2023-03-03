class DataSourceConnection
{
    protected DataSource m_DataSource;
    protected RestContext m_CurlContext;
    protected string m_RestRequestBody;

    DataSource GetDataSource()
    {
        return m_DataSource;
    };

    RestContext GetRestContext()
    {
        return m_CurlContext;
    };

    string GetRestRequestBody()
    {
        return m_RestRequestBody;
    };

    void DataSourceConnection(DataSource source);

    IDataSourceQuery CreateQuery();

    /**
     * @brief Releases this Connection object's database immediately instead of waiting for them to be automatically released.
     *        Calling the method close on a Connection object that is already closed is a no-op.
     *        It is strongly recommended that an application explicitly commits or rolls back an active transaction prior to calling the close method. 
     *        If the close method is called and there is an active transaction, the results are implementation-defined
     */
    void Close();
};