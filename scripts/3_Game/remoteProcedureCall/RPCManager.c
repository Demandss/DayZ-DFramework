/*
 This code powered by ©Demands.
 at 5/11/2022
*/

enum DRPCSingleplayerExecuteType
{
    Server,
    Client,
    Both
}

enum DRPCType
{
    Server,
    Client
};

class DRPCWrapper
{
    protected Class INSTANCE;
    protected int SPExecuteType;

    void DRPCWrapper(Class _instance, int _spExecuteType)
    {
        INSTANCE = _instance;
        SPExecuteType = _spExecuteType;
    };

    Class Get() { return INSTANCE; };

    int GetSPExecuteType() { return SPExecuteType; };
};

class DRPCManager
{
    static const int DFRAMEWORK_RPC_ID = 44046;
    
    protected autoptr map<string, ref map<string, ref DRPCWrapper>> m_RPCDataBase = new map<string, ref map<string, ref DRPCWrapper>>;

    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        Param2<string,string> data;
        if (!ctx.Read(data))
        {
            GetLogger().Error("Failure reading the RPC data from ParamsReadContext");
            return;
        }

        string modName = data.param1;
        string function = data.param2;

        string receivedFrom = "Server";
        if (GetGame().IsDedicatedServer())
        {
            if (sender == NULL)
            {
                GetLogger().Error("RPC was received from an invalid sender");
                return;
            }
            receivedFrom = sender.GetPlainId();
        }

        map<string, ref DRPCWrapper> functions;
        if (m_RPCDataBase.Find(modName,functions))
        {
            DRPCWrapper wrapper;
            if (functions.Find(function, wrapper))
            {
                auto functionData = new Param4<DRPCType, ParamsReadContext, PlayerIdentity, Object>(DRPCType.Server, ctx, sender, target);

                if ( ( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Server || wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Both ) ))
                {
                    GetGame().GameScript.CallFunctionParams( wrapper.Get(), function, NULL, functionData );
                }
                if ( ( GetGame().IsClient() && GetGame().IsMultiplayer() ) || ( GetGame().IsClient() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Client || wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Both ) ))
                {
                    functionData.param1 = DRPCType.Client;
                    GetGame().GameScript.CallFunctionParams( wrapper.Get(), function, NULL, functionData );
                }
                return;
            }
        }
        GetLogger().Warning(string.Format("%1 tried sending %2::%3 which does not seem to exist!",receivedFrom, modName, function));
    };

    void RPC(string modName, string function, ref Param params = NULL, bool guaranteed = false, ref PlayerIdentity identity = NULL, ref Object target = NULL)
    {
        auto data = new array< ref Param >;
		data.Insert( new Param2< string, string >( modName, function ) );
		data.Insert( params );
		
		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCDataBase.Contains( modName ) )
			{
				if ( m_RPCDataBase[ modName ].Contains( function ) )
				{
					DRPCWrapper wrapper = m_RPCDataBase[ modName ][ function ];
					
					if ( ( wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Both ) )
					{
						data.Insert( params );
					}
				}
			}
		}

		GetGame().RPC( target, DFRAMEWORK_RPC_ID, data, guaranteed, identity );
    };

    void RPCs( string modName, string function, ref array< ref Param > params, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
	{
		params.InsertAt( new Param2< string, string >( modName, function ), 0 );

		GetGame().RPC( sendToTarget, DFRAMEWORK_RPC_ID, params, guaranteed, sendToIdentity );

		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCDataBase.Contains( modName ) )
			{
				if ( m_RPCDataBase[ modName ].Contains( function ) )
				{
					DRPCWrapper wrapper = m_RPCDataBase[ modName ][ function ];
					
					if ( ( wrapper.GetSPExecuteType() == DRPCSingleplayerExecuteType.Both ) )
					{
                        GetLogger().Warning(string.Format("%1::%2 does not support DRPCSingleplayerExecuteType.Both when using DRPCManager::SendRPCs, use DRPCManager::SendRPC instead!",modName, function));
                    }
				}
			}
		}
	};

    void Register(string modName, string function, Class instense, int spExecuteType = DRPCSingleplayerExecuteType.Server)
    {
        if (!m_RPCDataBase.Contains(modName))
        {
            m_RPCDataBase.Set(modName, new map<string, ref DRPCWrapper>);
        }

        m_RPCDataBase[modName].Set(function,new DRPCWrapper(instense, spExecuteType));
    };
};

static ref DRPCManager g_DRPCManager;

static DRPCManager GetDRPCManager()
{
	if ( !g_DRPCManager )
		g_DRPCManager = new DRPCManager();

	return g_DRPCManager;
}