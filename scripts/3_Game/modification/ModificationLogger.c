class ModificationLogger extends Logger
{
    private string m_PluginName;

    void ModificationLogger(Modification mod)
    {
        string prefix = mod.GetDescription().GetPrefix();

        if (prefix != "")
            this.m_PluginName = "[" + prefix + "] ";
        else
            this.m_PluginName = "[" + mod.GetName() + "] ";
    };

    override void Log(LogLevel level, string message)
    {
        if (isCancelled()) return;

        string name = level.GetName();
        string msg;

        if (name != string.Empty)
            msg += string.Format(LOG_PREFIX,name) + m_PluginName;

        msg += message;

        currentLogFile.Println(msg);
    };
};