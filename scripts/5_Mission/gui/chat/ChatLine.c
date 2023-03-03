modded class ChatLine
{
    override void Set(ChatMessageEventParams params)	// Param 1 --> Channel, Param 2 --> sender name, Param 3 --> message, Param 4 ?? 
	{
		int channel; 
		
		m_NameWidget.SetText("");
		m_TextWidget.SetText("");
		
        if ((params.param4).Contains("0x"))
            SetColour(ColorUtility.ColorHexToInt(params.param4));
        else
            SetColour(DEFAULT_COLOUR);

		m_RootWidget.Show(true);
		
		channel = params.param1; // 0 = Survior   1 = Game/System   2 = Admin 
		
		if ( channel & CCSystem )
		{
			// Game
			if (params.param2 != "")
			{
				m_NameWidget.SetText(GAME_PREFIX + ": " );
			}

            if ((params.param4).Contains("0x"))
                SetColour(ColorUtility.ColorHexToInt(params.param4));
            else
                SetColorByParam(params.param4, GAME_TEXT_COLOUR);
		}
		else if ( channel & CCAdmin )
		{
			// Admin
			m_NameWidget.SetText(ADMIN_PREFIX + ": ");

            if ((params.param4).Contains("0x"))
                SetColour(ColorUtility.ColorHexToInt(params.param4));
            else
                SetColorByParam(params.param4, ADMIN_TEXT_COLOUR);
		}
		else if ( channel & CCTransmitter )
		{
			// Radio - Trasnmitter
			m_NameWidget.SetText(RADIO_PREFIX + params.param2 + " : ");
		}
		else if ( channel == 0 || channel & CCDirect )
		{
			// Player
			if (params.param2 != "")
			{
				m_NameWidget.SetText(params.param2 + " : ");
			}
		}

		m_TextWidget.SetText(params.param3);		

		m_FadeTimer.FadeIn(m_RootWidget, FADE_IN_DURATION);
		m_TimeoutTimer.Run(FADE_TIMEOUT, m_FadeTimer, "FadeOut", new Param2<Widget, float>(m_RootWidget, FADE_OUT_DURATION));
	}
};