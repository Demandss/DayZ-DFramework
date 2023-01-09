class CfgPatches
{
	class DFramework
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts","DZ_Data","DZ_Structures","DZ_Characters"};
	};
};

class CfgMods
{
	class DFramework
	{
		name = "Demands Framework";
		dir = "DFramework";
		credits = "Demands";
		author = "Demands";
		overview = "powered by Demands";
		type = "mod";
		dependencies[] = {"Core","Game","World","Mission"};
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/1_Core"};
			};
			class gameLibScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/2_GameLib"};
			};
			class gameScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/5_Mission"};
			};
		};
	};
};