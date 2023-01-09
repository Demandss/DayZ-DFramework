/*
 This code powered by ©Demands.
 at 23/07/2022
 */

modded class DayZGame
{
	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == DRPCManager.DFRAMEWORK_RPC_ID)
		{
            GetDRPCManager().OnRPC(sender, target, rpc_type, ctx);
			return;
		}
		super.OnRPC(sender, target, rpc_type, ctx);
    };
};