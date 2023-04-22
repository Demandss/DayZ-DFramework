/*
 This code powered by ©Demands.
 at 04/06/2023
 */

class DayZModification extends ModificationBase
{
    private ref ModificationDescription m_Description = NULL;
    private ref ModificationLogger m_Logger = NULL;

    void Init(string cfgModName)
    {
        this.m_Description = ModificationDescription(this,cfgModName);
        m_Logger = new ModificationLogger(this);
        this.OnInit();
    };

    ref ModificationDescription GetDescription() 
    {
        return this.m_Description;
    };

    ref ModificationLogger GetLogger() {
        return this.m_Logger;
    }
};