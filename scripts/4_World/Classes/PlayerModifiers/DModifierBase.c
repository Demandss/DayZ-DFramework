/*
 This code powered by ©Demands.
 at 10/06/2022
 */

class DModifierBase
{
    protected DString m_Identifier = string.Empty;
	protected PlayerBase m_Player;
	protected DModifiersManager m_Manager;
	protected int m_ActivityTime;
	protected bool m_TrackActivityTime;
	protected bool m_IsPersistent;
	protected bool m_IsActive;
	protected bool m_ShouldBeActive;
	protected bool m_IsLocked = false;
	protected EActivationType m_ActivationType;
	protected PluginPlayerStatus m_ModulePlayerStatus;

	void DModifierBase()
	{
		Class.CastTo(m_ModulePlayerStatus, GetPlugin(PluginPlayerStatus));
	};

    /**
     * @brief Initializes and registers a modifier and passes some data to it...
     */
    void RegisterModifer(PlayerBase player, DModifiersManager manager)
    {
		m_Player = player;
        m_Manager = manager;

        Init();
    };

    /**
     * @brief For those who need to do something during modifier initialization...
     */
    protected void Init() {};

	string GetIdentifier()
	{
		return m_Identifier;
	};

    PlayerBase GetPlayer()
    {
        return m_Player;
    };
	
	bool IsActive()
	{
		return m_IsActive;
	};

	bool IsTrackActivityTime()
	{
		return m_TrackActivityTime;
	};

	int GetActivityTime()
	{
		return m_ActivityTime;
	};

	void SetActivityTime(int val)
	{
		m_ActivityTime = val;
	};

	bool IsPersistent()
	{
		return m_IsPersistent;
	};
	
	void SetLock(bool state)
	{
		m_IsLocked = state;
	};

	bool IsLocked()
	{
		return m_IsLocked;		
	};

	/**
	 * @brief is called when an inactive modifier gets activated during gameplay,
	 * 		  is NOT called on activation upon player server connection(see OnReconnect).
	 */
	protected void OnActivate() {};
	
	/**
	 * @brief is called when a modifier is being re-activated upon player server connection, 
	 * 		  use to activate systems which are not persistent and need to run alongside active modifiers.
	 */
	protected void OnReconnect() {};

	protected void OnDeactivate() {};

	protected bool ActivateCondition()
	{
		return false;
	};

	protected bool DeactivateCondition()
	{
		return false;
	};

	void ActivateRequest(EActivationType trigger)
	{
		m_ShouldBeActive = true;
		m_ActivationType = trigger;
	};

	void Activate()
	{
		m_IsActive = true;

		if( m_ActivationType == EActivationType.TRIGGER_EVENT_ON_ACTIVATION )
			OnActivate();
		else if(m_ActivationType == EActivationType.TRIGGER_EVENT_ON_CONNECT ) 
			OnReconnect();

		m_Player.SetSynchDirty();
	};

	void Deactivate()
	{
		if(!IsActive())
			return;

		m_ShouldBeActive = false;
		m_IsActive = false;

		m_ActivityTime = 0;

		OnDeactivate();
	};

	protected void OnTick() {};

	void Tick()
	{
		OnTick();

		if( !IsActive() && m_ShouldBeActive )
		{
			Activate();
		}

		if (IsActive())
		{
			if (DeactivateCondition() && !IsLocked())
				Deactivate();
			else
			{
				m_ActivityTime += TICK_FREQUENCY_MILLIS;
				OnTick();
			}
		}
		else
		{
			if( ActivateCondition() )
			{
				if( !IsLocked() ) 
				{
					ActivateRequest(EActivationType.TRIGGER_EVENT_ON_ACTIVATION);
				}
			}
		}
	};

	void OnStoreSave( ParamsWriteContext ctx ) {};
	bool OnStoreLoad( ParamsReadContext ctx) {};
};