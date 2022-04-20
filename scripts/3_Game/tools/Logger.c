/*
 This code powered by ©Demands.
 at 4/19/2022
 */

class Logger
{
    private const string LOG_FOLDER = "$profile:logs";
    private const string LOG_PREVIUS_FILENAME = "log-%1.oldlog";
    private const string LOG_FILENAME = "latest.log";

    private const string LOG_PREFIX = "[%1]";

    private bool canInitialize = true;
    private static FileHandle currentLogFile;
    
    void ~Logger()
    {
        if (!CanInitialize()) return;

        FPrintln(currentLogFile, "***Logger successfully deinitialized***");

        currentLogFile.Close();
    };

    /**
     * @brief needed only to create a log folder and file
     */
    static Initialize()
    {
        if (!FileExist(LOG_FOLDER)) MakeDirectory(LOG_FOLDER);

        if (!CanInitialize()) return;

        string filePath = LOG_FOLDER + LOG_FILENAME;
        string previusFilePath = LOG_FOLDER + LOG_PREVIUS_FILENAME;

        if (!FileExist(LOG_FOLDER) || !currentLogFile)
        {
            currentLogFile = OpenFile(filePath,FileMode.WRITE);
        }
        else
        {
            DataTime data = DataTime.Now();

            CopyFile(filePath,string.Format(previusFilePath,data.toString1()));
            DeleteFile(filePath);

            currentLogFile = OpenFile(filePath,FileMode.WRITE);
        }

        FPrintln(currentLogFile, "***Logger successfully initialized***");
    };

    static bool CanInitialize() {return canInitialize;};

    /**
     * @brief Allows to stop the logger at the conception level if pass "true" 
     * 
     * @param var 
     */
    static void SetCanseleble(bool var) {canInitialize = !var};

    static void Log(LogLevel level, string message)
    {
        if (!CanInitialize()) return;

        string msg = string.Format(LOG_PREFIX,level.GetName());
        msg += message;

        GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Call(LogThreaded,msg);
    };

    private void LogThreaded(string msg)
    {
        FPrintln(currentLogFile,msg);
    };

    static void Warning(string msg) {Log(LogLevel.WARNING,msg);};

    static void Info(string msg) {Log(LogLevel.INFO,msg);};
};