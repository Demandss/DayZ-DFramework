class Bootstrap
{
    void PreInit()
    {
        GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Call(DFramework.InitializeLogger);
    };

    void Init()
    {
        
    };

    void PostInit()
    {
        
    };
};