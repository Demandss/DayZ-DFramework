class ModificationManager
{
    private ref array<ref Modification> m_Modifications = new array<ref Modification>;
    private ref map<string,ref Modification> m_LookupNames = new map<string,ref Modification>;

    void LoadModification(typename main, string modName)
    {
        ref DayZModification mod = main.Spawn();
        modName.Replace(" ", "_");

        mod.Init(modName);

        this.m_Modifications.Insert(mod);
        this.m_LookupNames.Insert(mod.GetName(), mod);
    };

    void LoadModificationsDescriptionData()
    {
        foreach (DayZModification mod : m_Modifications)
        {
            mod.GetDescription().InitData();
        }
    };

    ref array<ref Modification> GetModifications()
    {
        return m_Modifications;
    };

    ref Modification GetModification(string name)
    {
        name.Replace(" ", "_");
        return this.m_LookupNames.Get(name);
    };
};