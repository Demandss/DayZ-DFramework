class PlayerHitedEvent extends PlayerEvent
{
    protected static ref HandlerList m_Handlers = new HandlerList();
    protected TotalDamageResult m_DamageResult;
    protected int m_DamageType;
    protected EntityAI m_Source;
    protected int m_Component;
    protected string m_DmgZone;
    protected string m_Ammo;
    protected vector m_ModelPos;
    protected float m_SpeedCoef;

    void PlayerHitedEvent(PlayerBase _player, TotalDamageResult _damageResult, int _damageType, EntityAI _source, int _component, string _dmgZone, string _ammo, vector _modelPos, float _speedCoef)
    {
        m_Player = _player;
        this.m_DamageResult = _damageResult;
        this.m_DamageType = _damageType;
        this.m_Source = _source;
        this.m_Component = _component;
        this.m_DmgZone = _dmgZone;
        this.m_Ammo = _ammo;
        this.m_ModelPos = _modelPos;
        this.m_SpeedCoef = _speedCoef;
    };

    TotalDamageResult GetDamageResult()
    {
        return this.m_DamageResult;
    };

    int GetDamageType()
    {
        return this.m_DamageType;
    };

    EntityAI GetHitSource()
    {
        return this.m_Source;
    };

    int GetComponent()
    {
        return this.m_Component;
    };

    string GetDmgZone()
    {
        return this.m_DmgZone;
    };

    string GetAmmo()
    {
        return this.m_Ammo;
    };

    vector GetModelPos()
    {
        return this.m_ModelPos;
    };

    float GetSpeedCoef()
    {
        return this.m_SpeedCoef;
    };

    override ref HandlerList GetHandlers() 
    {
        return m_Handlers;
    };

    override static ref HandlerList GetHandlerList() 
    {
        return m_Handlers;
    };
}