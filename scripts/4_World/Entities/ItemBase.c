modded class ItemBase
{
	protected EffectSound m_DFSound;
    protected Particle m_DFParticle;
    protected PointLightBase m_DFLight;

    void ~ItemBase()
    {
        DestroyEffects();
    };

    override void EEInit()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ActivateEffects, 100, false);
        super.EEInit();
    };

    void DestroyEffects()
    {
        if (m_DFLight)
        {
            m_DFLight.Destroy();
            m_DFLight = NULL;
        }
        if (m_DFParticle)
        {
            m_DFParticle.StopParticle();
            m_DFParticle = NULL;
        }
        if (m_DFSound)
        {
            m_DFSound.Stop();
            m_DFSound = NULL;
        }
    };

    void ActivateEffects()
    {
        DestroyEffects();
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer())
        {
            string configDataPath = string.Format("CfgVehicles %1 Effects",this.GetType());
            if (!GetGame().ConfigIsExisting(configDataPath))
                return;

            if (GetGame().ConfigIsExisting(configDataPath + " Sound"))
            {
                string soundName = GetGame().ConfigGetTextOut(configDataPath + " Sound name");
                if (soundName != "")
                {
                    float soundFadeIn = GetGame().ConfigGetFloat(configDataPath + " Sound fadeIn");
                    float soundFadeOut = GetGame().ConfigGetFloat(configDataPath + " Sound fadeOut");
                    bool soundLoop = ConfigGetBool(configDataPath + " Sound loop");

                    PlaySoundSet(m_DFSound,soundName,soundFadeIn,soundFadeOut,soundLoop);
                    m_DFSound.SetSoundAutodestroy(true);
                }
            }

            if (GetGame().ConfigIsExisting(configDataPath + " Particle"))
            {
                string particleIdStr = GetGame().ConfigGetTextOut(configDataPath + " Particle identifier");
                if (particleIdStr != "")
                {
                    vector particlePosition = GetGame().ConfigGetVector(configDataPath + " Particle position");

                    int particleId = ParticleList.GetParticleIDByName(particleIdStr);

                    if (!ParticleList.IsValidId(particleId))
                        particleId = ParticleList.GetParticleID(particleIdStr);

                    m_DFParticle = Particle.PlayOnObject(particleId, this, particlePosition);
                }
            }

            if (GetGame().ConfigIsExisting(configDataPath + " Light"))
            {
                string lightTypeStr = GetGame().ConfigGetTextOut(configDataPath + " Light type");
                if (lightTypeStr != "")
                {
                    float lightFadeInTime = GetGame().ConfigGetFloat(configDataPath + " Light fadeInTime");
                    vector lightPosition = GetGame().ConfigGetVector(configDataPath + " Light position");
        
                    m_DFLight = ScriptedLightBase.CreateLight(lightTypeStr.ToType(), lightPosition, lightFadeInTime);

                    if (m_DFLight)
                    {
                        if (GetGame().ConfigIsExisting(configDataPath + " Light memoryPointStart"))
                        {
                            string memoryPointStart = GetGame().ConfigGetTextOut(configDataPath + " Light memoryPointStart");
                            string memoryPointTarget = GetGame().ConfigGetTextOut(configDataPath + " Light memoryPointTarget");

                            m_DFLight.AttachOnMemoryPoint(this,memoryPointStart,memoryPointTarget);
                        }
                        else
                        {
                            vector lightOrientation = GetGame().ConfigGetVector(configDataPath + " Light orientation");
                            m_DFLight.AttachOnObject(this, lightPosition, lightOrientation);
                        }
                    }
                }
            }
        }
    };

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        if (newLoc)
        {
            if (newLoc.GetType() == InventoryLocationType.HANDS || newLoc.GetType() == InventoryLocationType.GROUND)
                ActivateEffects();
            else
                DestroyEffects();
        }
        super.EEItemLocationChanged(oldLoc,newLoc);
    };
};