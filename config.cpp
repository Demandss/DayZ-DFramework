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
		name = "Dick Framework";
		dir = "DFramework";
		credits = "Demands";
		author = "Demands";
		overview = "powered by Demands";
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] = {"DFramework/scripts/1_Core"};
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