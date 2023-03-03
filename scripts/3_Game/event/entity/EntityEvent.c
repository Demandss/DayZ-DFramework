/*
 This code powered by ©Demands.
 at 01/09/2023
 */

class DEntityEvent extends DEvent {
    protected EntityAI m_Entity;

    EntityAI GetEntity() { return this.m_Entity; };

    string GetEntityType() { return this.m_Entity.GetType(); };
};