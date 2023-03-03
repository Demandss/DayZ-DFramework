/*
 This code powered by ©Demands.
 at 5/11/2022
*/

enum DRPCType
{
    Server,
    Client
};

class DRPCWrapper
{
    protected Class INSTANCE;
    protected DExecuteSide SPExecuteType;

    void DRPCWrapper(Class _instance, DExecuteSide _spExecuteType)
    {
        INSTANCE = _instance;
        SPExecuteType = _spExecuteType;
    };

    Class Get() { return INSTANCE; };

    DExecuteSide GetSPExecuteType() { return SPExecuteType; };
};

class DRPCManager
{
    static const int DFRAMEWORK_RPC_ID = 10090;
    
    protected autoptr map<ref DayZModification, ref map<string, ref DRPCWrapper>> m_RPCDataBase = new map<ref DayZModification, ref map<string, ref DRPCWrapper>>;

    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        Param2<ref DayZModification,string> data;
        if (!ctx.Read(data))
        {
            GetDFLogger().Error("Failure reading the RPC data from ParamsReadContext");
            return;
        }

        DayZModification modification = data.param1;
        string function = data.param2;

        string receivedFrom = "Server";
        if (GetGame().IsDedicatedServer())
        {
            if (sender == NULL)
            {
                GetDFLogger().Error("RPC was received from an invalid sender");
                return;
            }
            receivedFrom = sender.GetPlainId();
        }

        map<string, ref DRPCWrapper> functions;
        if (m_RPCDataBase.Find(modification,functions))
        {
            DRPCWrapper wrapper;
            if (functions.Find(function, wrapper))
            {
                auto functionData = new Param4<DRPCType, ParamsReadContext, PlayerIdentity, Object>(DRPCType.Server, ctx, sender, target);

                if ( ( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecuteType() == DExecuteSide.Server || wrapper.GetSPExecuteType() == DExecuteSide.Both ) ))
                {
                    GetGame().GameScript.CallFunctionParams( wrapper.Get(), function, NULL, functionData );
                }
                if ( ( GetGame().IsClient() && GetGame().IsMultiplayer() ) || ( GetGame().IsClient() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecuteType() == DExecuteSide.Client || wrapper.GetSPExecuteType() == DExecuteSide.Both ) ))
                {
                    functionData.param1 = DRPCType.Client;
                    GetGame().GameScript.CallFunctionParams( wrapper.Get(), function, NULL, functionData );
                }
                return;
            }
        }
        GetDFLogger().Warning(string.Format("%1 tried sending %2::%3 which does not seem to exist!",receivedFrom, modification, function));
    };

    void RPCSingleParam(DayZModification modification, string function, ref Param params = NULL, bool guaranteed = false, ref PlayerIdentity identity = NULL, ref Object target = NULL)
    {
        auto data = new array< ref Param >;
		data.Insert( new Param2<ref DayZModification, string >( modification, function ) );
		data.Insert( params );
		
		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCDataBase.Contains( modification ) )
			{
				if ( m_RPCDataBase[ modification ].Contains( function ) )
				{
					DRPCWrapper wrapper = m_RPCDataBase[ modification ][ function ];
					
					if ( ( wrapper.GetSPExecuteType() == DExecuteSide.Both ) )
					{
						data.Insert( params );
					}
				}
			}
		}

		GetGame().RPC( target, DFRAMEWORK_RPC_ID, data, guaranteed, identity );
    };

    void RPCParams(DayZModification modification, string function, ref array< ref Param > params, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
	{
		params.InsertAt( new Param2< ref DayZModification, string >( modification, function ), 0 );

		GetGame().RPC( sendToTarget, DFRAMEWORK_RPC_ID, params, guaranteed, sendToIdentity );

		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCDataBase.Contains( modification ) )
			{
				if ( m_RPCDataBase[ modification ].Contains( function ) )
				{
					DRPCWrapper wrapper = m_RPCDataBase[ modification ][ function ];
					
					if ( ( wrapper.GetSPExecuteType() == DExecuteSide.Both ) )
					{
                        GetDFLogger().Warning(string.Format("%1::%2 does not support DExecuteSide.Both when using DRPCManager::RPCParams, use DRPCManager::RPCSingleParam instead!",modification, function));
                    }
				}
			}
		}
	};

    void ScriptRPC(DayZModification modification, string function, ref ScriptRPC rpc, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
	{
        rpc.Write(new Param2<ref DayZModification, string >( modification, function ));
		rpc.Send(sendToTarget, DFRAMEWORK_RPC_ID, true, sendToIdentity);
	};

    void Register(DayZModification modification, string function, Class instense, int spExecuteType = DExecuteSide.Server)
    {
        if (!m_RPCDataBase.Contains(modification))
        {
            m_RPCDataBase.Set(modification, new map<string, ref DRPCWrapper>);
        }

        m_RPCDataBase[modification].Set(function,new DRPCWrapper(instense, spExecuteType));
    };
};

static ref DRPCManager g_DRPCManager;

static DRPCManager GetDRPCManager()
{
	if ( !g_DRPCManager )
		g_DRPCManager = new DRPCManager();

	return g_DRPCManager;
}