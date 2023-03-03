class ModificationDescription
{
    private string m_Name = string.Empty;
    private string m_FullName;
    private string m_Prefix;
    private ref Class m_Main = NULL;
    private string m_Directory;
    private string m_Credits;
    private string m_Author;
    private string m_Overview;
    private ref TStringArray m_Dependencies = new TStringArray;
    private ref set<string> m_RequiredAddons = new set<string>;
    // private ref array<ref Permission> m_Permissions;

    void ModificationDescription(Class main, string modName = string.Empty)
    {
        this.m_Main = main;
        this.m_Name = modName;

    };

    void InitData()
    {
        if (m_Name == string.Empty) return;

        string configDataPath = string.Format("CfgMods %1",m_Name);

        if (GetGame().ConfigIsExisting(configDataPath + " name"))
            m_FullName = GetGame().ConfigGetTextOut(configDataPath + " name");
        if (GetGame().ConfigIsExisting(configDataPath + " prefix"))
            m_Prefix = GetGame().ConfigGetTextOut(configDataPath + " prefix");
        if (GetGame().ConfigIsExisting(configDataPath + " dir"))
            m_Directory = GetGame().ConfigGetTextOut(configDataPath + " dir");
        if (GetGame().ConfigIsExisting(configDataPath + " credits"))
            m_Credits = GetGame().ConfigGetTextOut(configDataPath + " credits");
        if (GetGame().ConfigIsExisting(configDataPath + " author"))
            m_Author = GetGame().ConfigGetTextOut(configDataPath + " author");
        if (GetGame().ConfigIsExisting(configDataPath + " overview"))
            m_Overview = GetGame().ConfigGetTextOut(configDataPath + " overview");
        if (GetGame().ConfigIsExisting(configDataPath + " dependencies"))
            GetGame().ConfigGetTextArray(configDataPath + " dependencies", m_Dependencies);

        configDataPath = string.Format("CfgPatches %1",m_Name);

        if (GetGame().ConfigIsExisting(configDataPath + " requiredAddons"))
        {
            TStringArray requiredAddons = new TStringArray;
            GetGame().ConfigGetTextArray(configDataPath + " requiredAddons", requiredAddons);

            foreach(string addon : requiredAddons)
                m_RequiredAddons.Insert(addon);
        }
    };

    string GetName()
    {
        return m_Name;
    };

    string GetFullName()
    {
        return m_FullName;
    };

    string GetPrefix()
    {
        return m_Prefix;
    };

    Class GetMain()
    {
        return m_Main;
    };

    string GetDirectory()
    {
        return m_Directory;
    };

    string GetCredits()
    {
        return m_Credits;
    };

    string GetAuthor()
    {
        return m_Author;
    };

    string GetOverview()
    {
        return m_Overview;
    };

    ref array<string> GetDependencies()
    {
        return m_Dependencies;
    };

    ref set<string> GetRequiredAddons()
    {
        return m_RequiredAddons;
    };
/* 
    ref array<ref Permission> GetPermissions()
    {
        return m_Permissions;
    }; */
};