/*
 This code powered by ©Demands.
 at 4/19/2022
 */

class Logger
{
    private static const string LOG_FOLDER = "$profile:logs";
    private static const string LOG_PREVIUS_FILENAME = "log-%1.oldlog";
    private static const string LOG_FILENAME = "latest.log";

    private static const string LOG_PREFIX = "[%1]";

    private static bool canInitialize = true;
    private static FileHandle currentLogFile;
    
    void ~Logger()
    {
        if (!isCancelled()) return;

        FPrintln(currentLogFile, "***Logger successfully deinitialized***");
    };

    /**
     * @brief needed only to create a log folder and file
     */
    static void Initialize()
    {
        if (!FileExist(LOG_FOLDER)) MakeDirectory(LOG_FOLDER);

        if (!isCancelled()) return;

        string filePath = LOG_FOLDER + LOG_FILENAME;
        string previusFilePath = LOG_FOLDER + LOG_PREVIUS_FILENAME;

        if (!FileExist(LOG_FOLDER) || !currentLogFile)
        {
            currentLogFile = OpenFile(filePath,FileMode.WRITE);
        }
        else
        {
            DataTime data = DataTime();

            CopyFile(filePath,string.Format(previusFilePath,data.ToString2()));
            DeleteFile(filePath);

            currentLogFile = OpenFile(filePath,FileMode.WRITE);
        }

        FPrintln(currentLogFile, "***Logger successfully initialized***");
    };

    static bool isCancelled() {return canInitialize;};

    /**
     * @brief Allows to stop the logger at the conception level if pass "true" 
     * 
     * @param var 
     */
    static void SetCancelled(bool var) {canInitialize = !var};

    static void Log(LogLevel level, string message)
    {
        if (!isCancelled()) return;
        string name = level.GetName();
        string msg = string.Format(LOG_PREFIX,name);
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