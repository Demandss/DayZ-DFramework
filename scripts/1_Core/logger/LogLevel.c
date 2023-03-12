/*
 This code powered by ©Demands.
 at 4/19/2022
 */

enum LogType 
{
    ERROR = 1000,
    WARNING = 900,
    DEBUG = 800,
    INFO = 700,
    NONE = 0,
};

class LogLevel 
{
    private string m_Name;
    
    private int m_Value;

    /**
     * @brief ERROR is a message level indicating a serious failure.
     * 
     * In general ERROR message should describe events that are of 
     * considerable importance and which will prevent normal execution.
     * They should be reasonable intelligible to end users.
     *
     * This level is initialized to 1000.
     */
    static const LogLevel ERROR = new LogLevel("ERROR",LogType.ERROR);
    /**
     * @brief WARNING is a message level indicating a potential problem.
     * 
     * In general WARNING message should describe events that will be
     * of interest to end users, or which indicate potential problems.
     * 
     * This level is initialized to 900.
     */
    static const LogLevel WARNING = new LogLevel("WARNING",LogType.WARNING);
    /**
     * @brief DEBUG is a message level for code debugging messages.
     *
     * Anything can be in DEBUG, it was created for debugging
     * messages for problem areas of code.
     * 
     * This level is initialized to 800.
     */
    static const LogLevel DEBUG = new LogLevel("DEBUG",LogType.DEBUG);
    /**
     * @brief INFO is a message level for informational messages.
     *
     * Typically INFO messages will be written to the console or its equivalent,
     * but given that in DayZ this is very problematic, they will be output to the log file. ¯\_(ツ)_/¯
     * So the INFO level should only be used for reasonable significant messages that will
     * make sense to end users.
     * 
     * This level is initialized to 700.
     */
    static const LogLevel INFO = new LogLevel("INFO",LogType.INFO);
    /**
     * @brief This is necessary to display any messages in the log file. This level is initialized to 0.
     */
    static const LogLevel NONE = new LogLevel(string.Empty,LogType.NONE);

    private static const autoptr array<LogType> standardLevels = {
        LogType.DEBUG, LogType.INFO, LogType.WARNING, LogType.ERROR, LogType.NONE
    };

    protected void LogLevel(string name, int value)
    {
        m_Name = name;
        m_Value = value;
    };

    string GetName() {return m_Name;};

    string ToString1() {return m_Name;};

    int GetValue() {return m_Value;};
};