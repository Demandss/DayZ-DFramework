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

    private static bool canInitialize = false;
    private static DFile currentLogFile;
    private static FileHandle currentLogFile;
    
    void ~Logger()
    {
        if (isCancelled()) return;
        
        currentLogFile.Println("***Logger successfully deinitialized***");
    };

    /**
     * @brief needed only to create a log folder and file
     */
    static void Initialize()
    {
        if (isCancelled()) return;

        string filePath = LOG_FOLDER + LOG_FILENAME;
        string previusFilePath = LOG_FOLDER + LOG_PREVIUS_FILENAME;

        currentLogFile = new DFile(filePath);

        if (FileExist(filePath))
        {
            DataTime data = DataTime();
            currentLogFile.Rename(string.Format(previusFilePath,data.ToString2()));
        }

        currentLogFile = new DFile(filePath);

        currentLogFile.Println("***Logger successfully initialized***");
    };

    static bool isCancelled() {return canInitialize;};

    /**
     * @brief Allows to stop the logger at the conception level if pass "true" 
     */
    static void SetCancelled(bool var) {canInitialize = var};

    /**
     * @brief According to the specified logging level, displays a message in latest.log, 
     *       supports auto-formatting of text for additional parameters.
     */
    static void Log(LogLevel level, string message, void param1=NULL, void param2=NULL, void param3=NULL, void param4=NULL, void param5=NULL, void param6=NULL, void param7=NULL, void param8=NULL, void param9=NULL)
    {
        if (!isCancelled()) return;
        string name = level.GetName();
        string msg = string.Format(LOG_PREFIX,name) + " ";
        msg += message;
        msg = string.Format(msg,param1,param2,param3,param4,param5,param6,param7,param8,param9);

        GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Call(LogThreaded,msg);
    };

    private void LogThreaded(void msg)
    {
        FPrintln(currentLogFile,msg);
    };

    static void Warning(string msg, void param1=NULL, void param2=NULL, void param3=NULL, void param4=NULL, void param5=NULL, void param6=NULL, void param7=NULL, void param8=NULL, void param9=NULL) 
    {
        Log(LogLevel.WARNING,msg,param1,param2,param3,param4,param5,param6,param7,param8,param9);
    };

    static void Info(string msg, void param1=NULL, void param2=NULL, void param3=NULL, void param4=NULL, void param5=NULL, void param6=NULL, void param7=NULL, void param8=NULL, void param9=NULL) 
    {
        Log(LogLevel.INFO,msg,param1,param2,param3,param4,param5,param6,param7,param8,param9);
    };
};