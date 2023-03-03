modded class ChatInputMenu
{
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (!finished) return false;
		
		string text = m_edit_box.GetText();

		if (text != "")
		{
			ScriptRPC rpc = new ScriptRPC();
			rpc.Write(new Param2<PlayerBase,string>(g_Game.GetPlayer(),text));
            GetDRPCManager().ScriptRPC(DFramework.Get(),"ChatMessageHander",rpc,true);
		}

		m_close_timer.Run(0.1, this, "Close");
		
		GetUApi().GetInputByName("UAPersonView").Supress();	
		
		return true;
	}
};