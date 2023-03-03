/*
 This code powered by ©Demands.
 at 4/19/2022
 */

class Logger
{
    protected const string LOG_FOLDER = "$profile:logs/";
    protected const string LOG_PREVIUS_FILENAME = "log_%1.log";
    protected const string LOG_FILENAME = "latest.log";

    protected const string LOG_PREFIX = "[%1]";

    protected bool cancelled = false;
    protected DFile currentLogFile;

    /**
     * @brief needed only to create a log folder and file.
     */
    void Initialize()
    {
        if (isCancelled()) return;

        string filePath = LOG_FOLDER + LOG_FILENAME;
        string previusFileName = LOG_PREVIUS_FILENAME;

        currentLogFile = new DFile(filePath);

        if (FileExist(filePath))
        {
            DataTime data = DataTime();
            currentLogFile.Rename(string.Format(previusFileName,data.ToString2()));
            currentLogFile = new DFile(filePath);
        }
    };

    bool isCancelled() {return cancelled;};

    /**
     * @brief Allows to stop the logger at the conception level if pass "true".
     */
    void SetCancelled(bool state) {cancelled = state};

    /**
    * @brief I don't know who will need this, but I'll leave it here just in case.
    */
    DFile GetFile() { return currentLogFile; };

    /**
     * @brief According to the specified logging level, displays a message in latest.log.
     */
    void Log(LogLevel level, string message)
    {
        if (isCancelled()) return;

        string name = level.GetName();
        string msg;

        if (name != string.Empty)
            msg += string.Format(LOG_PREFIX,name) + " ";

        msg += message;

        currentLogFile.Println(msg);
    };
    
    void Warning(string msg) 
    {
        Log(LogLevel.WARNING,msg);
    };
    
    void Error(string msg) 
    {
        Log(LogLevel.ERROR,msg);
    };

    void Info(string msg) 
    {
        Log(LogLevel.INFO,msg);
    };
};

static ref Logger dfLogger;

static ref Logger GetDFLogger()
{
    if (!dfLogger) dfLogger = new Logger;
    return dfLogger;
}