/*
 This code powered by ©Demands.
 at 10/06/2022
 */

class DModifiersManager
{
    protected PlayerBase m_Player;
    protected autoptr map<string,ref map<string,ref DModifierBase>> m_Modifiers;
	protected ref array<ref Param> m_Params;

    void DModifiersManager(PlayerBase player)
	{
		m_Modifiers = new map<string,ref map<string,ref DModifierBase>>;
		m_Params = new array<ref Param>;
		m_Player = player;

		Init();
	};
		
	PlayerBase GetPlayer()
	{
		return m_Player;
	}

    /**
     * @brief Registers a modifier into memory.
     * 
     * @param modifier - just pass your modifier as before.
     * @param modName - needed for those who do not want to face incompatibility with other modification.
     */
    void RegisterModifier(DModifierBase modifier, string modName = "DFramework")
	{
		modifier.RegisterModifer(m_Player,this);
        string identifier = modifier.GetIdentifier();

		if (identifier == string.Empty)
			GetDFLogger().Warning(string.Format("Maybe you forgot to specify your modifier identifier in %1",modifier.Type()));

        ref map<string,ref DModifierBase> _Modifiers;

        if (m_Modifiers.Contains(modName))
        {
            _Modifiers = m_Modifiers.Get(modName);

            if (_Modifiers.Contains(identifier))
            {
                GetDFLogger().Warning(string.Format("Why do you need two modifiers %1 and %2 with the same identifier %3",modifier.Type(),_Modifiers.Get(identifier).Type(),identifier));
                return;
            }
            
            _Modifiers.Insert(identifier,modifier);

            m_Modifiers.Set(modName,_Modifiers);
        }
        else
        {
            _Modifiers = new map<string,ref DModifierBase>;
            _Modifiers.Insert(identifier,modifier);
            
            m_Modifiers.Insert(modName,_Modifiers);
        }
	};

    void Init()	{};

    /**
     * @brief Will tell if this modifier is active.
     * 
     * @param modName - needed for those who do not want to face incompatibility with other modification.
     */
    bool IsModifierActive(string modifierIdentifier, string modName = "DFramework")
	{
		return m_Modifiers.Get(modName).Get(modifierIdentifier).IsActive();
	};

    ref array<ref DModifierBase> GetAllModifiers()
    {
        ref array<ref DModifierBase> modifiers = new array<ref DModifierBase>;

        foreach (map<string,ref DModifierBase> value : m_Modifiers.GetValueArray())
        {
            modifiers.InsertAll(value.GetValueArray());
        }

        return modifiers;
    };

    ref map<string,ref DModifierBase> GetModifiers(string modName = string.Empty)
    {
        ref map<string,ref DModifierBase> modifiers = new map<string,ref DModifierBase>;

        if (modName == string.Empty)
        {
            foreach (map<string,ref DModifierBase> value : m_Modifiers.GetValueArray())
            {
                foreach (string v : value.GetKeyArray())
                {
                    modifiers.Insert(v,value.Get(v));
                }
            }
        }
        else
        {
            modifiers = m_Modifiers.Get(modName);
        }

        return modifiers;
    }

	DModifierBase GetModifier(string modifierIdentifier, string modName = string.Empty)
	{
		return GetModifiers(modName).Get(modifierIdentifier);
	}

	void SetModifierLock(string modifierIdentifier, bool state, string modName = string.Empty)
	{
        GetModifier(modifierIdentifier,modName).SetLock(state);
	}

	bool GetModifierLock(string modifierIdentifier, string modName = string.Empty)
	{
		return GetModifier(modifierIdentifier,modName).IsLocked();
	}

    void DeactivateAllModifiers()
	{
        ref array<ref DModifierBase> modifiers = GetAllModifiers();

        if (!modifiers)
        {
            GetDFLogger().Warning("Custom modifiers are not found, maybe you made a mistake somewhere or they should not be, in this case, ignore this message.");
            return;
        }

        foreach(DModifierBase modifier: modifiers)
		{
			modifier.Deactivate();
		}
	};

    void ActivateModifier(string modifierIdentifier, bool triggerEvent = EActivationType.TRIGGER_EVENT_ON_ACTIVATION, string modName = string.Empty)
	{
        GetModifier(modifierIdentifier,modName).ActivateRequest(triggerEvent);
	}

	void DeactivateModifier(string modifierIdentifier, string modName = string.Empty)
	{
        GetModifier(modifierIdentifier,modName).Deactivate();
	}

    void OnScheduledTick()
	{
        ref array<ref DModifierBase> modifiers = GetAllModifiers();

        if (modifiers.Count() == 0) return;

		foreach(DModifierBase modifier: modifiers)
			modifier.Tick();
	};

    void OnStoreSave( ParamsWriteContext ctx )
	{
		CachedObjectsArrays.ARRAY_INT.Clear();
		CachedObjectsArrays.ARRAY_STRING.Clear();

		int modifier_count;
        foreach (DModifierBase modifier : GetAllModifiers())
        {
            if( modifier.IsActive() && modifier.IsPersistent() ) 
			{
                modifier_count++;

                modifier.OnStoreSave(ctx);

				CachedObjectsArrays.ARRAY_STRING.Insert( modifier.GetIdentifier() );
				if( modifier.IsTrackActivityTime() )
				{
					CachedObjectsArrays.ARRAY_INT.Insert( modifier.GetActivityTime() );
				}
            }
        }

		ctx.Write(modifier_count);

		for(int i = 0; i < CachedObjectsArrays.ARRAY_INT.Count(); i++)
		{
			int item = CachedObjectsArrays.ARRAY_INT.Get(i);

			ctx.Write(item);
		}
		for(int z = 0; z < CachedObjectsArrays.ARRAY_STRING.Count(); z++)
		{
			string item1 = CachedObjectsArrays.ARRAY_STRING.Get(i);

			ctx.Write(item1);
		}

		for (int j = 0; j < m_Params.Count(); j++)
		{
			m_Params.Get(j).Serialize(ctx);
		}
	};

	bool OnStoreLoad( ParamsReadContext ctx)
	{
		int modifier_count;
		if(!ctx.Read(modifier_count))
			return false;

		for(int i = 0; i < modifier_count; i++)
		{
			string modifierIdentifier;
			if(!ctx.Read(modifierIdentifier))
				return false;

			DModifierBase modifier = GetModifier(modifierIdentifier);
			if( modifier )
			{
                modifier.OnStoreLoad(ctx);

				if( modifier.IsTrackActivityTime() )
				{
					int time;
					if(!ctx.Read(time))
						return false;

					modifier.SetActivityTime( time );
				}
				
				ActivateModifier(modifierIdentifier, EActivationType.TRIGGER_EVENT_ON_CONNECT);
			}
			else
			{
                GetDFLogger().Error(string.Format("DB loading: non-existent modifier with id:%1",modifierIdentifier));
			}
		}
		
		for (int j = 0; j < m_Params.Count(); j++)
		{
			if(!m_Params.Get(j).Deserializer(ctx))
			{
				return false;
			}
		}
		return true;
	};
};