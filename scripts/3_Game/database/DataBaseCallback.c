class DataBaseCallback extends RestCallback
{
    private string m_Request;
    private ref Class m_ResultSendClassInst; 
    private string m_ResultSendFunction; 
    private ref Param m_ResultSendFunctionParams; 

    void DataBaseCallback(string request = string.Empty)
    {
        m_Request = request;
    };

    void SetRequest(string request)
    {
        m_Request = request;
    };

    void SetResultSendMethod(Class inst, string function)
    {
        m_ResultSendClassInst = inst;
        m_ResultSendFunction = function;
    };

    override void OnError( int errorCode )
	{
        GetDFLogger().Error("DataBase exeptoin ERestResultState::" + typename.EnumToString(ERestResultState, errorCode) + "");
	};

	override void OnTimeout()
	{    
        GetDFLogger().Error("DataBase execute update <" + m_Request + "> timeout");
	};

	override void OnSuccess( string data, int dataSize )
	{
        GetGame().GameScript.CallFunction(m_ResultSendClassInst, m_ResultSendFunction, NULL, new DataSourceQueryResult(data));
	};

	override void OnFileCreated( string fileName, int dataSize ) {};
};