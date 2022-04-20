class DataTime
{
    protected int m_Year;
    protected int m_Month;
    protected int m_Day;
    protected int m_Hour;
    protected int m_Minute;
    protected int m_Second;

    static DataTime Now()
    {
        DataTime data = new DataTime();
        
        GetYearMonthDayUTC(data.m_Year,data.m_Month,data.m_Day);
        GetHourMinuteSecondUTC(data.m_Hour,data.m_Minute,data.m_Second);

        return data;
    };

    static int GetYear() {return m_Year;};
    static int GetMonth() {return m_Month;};
    static int GetDay() {return m_Day;};
    static int GetHour() {return m_Hour;};
    static int GetMinute() {return m_Minute;};
    static int GetSecond() {return m_Second;};

    int GetTimeByType(TimeType type)
    {
        switch(type) 
        {
            case TimeType.SECOND:
            {
                return GetSecond();
                break;
            };
            case TimeType.MINUTE:
            {
                return GetMinute();
                break;
            };
            case TimeType.HOUR:
            {
                return GetHour();
                break;
            };
            case TimeType.DAY:
            {
                return GetDay();
                break;
            };
            case TimeType.MONTH:
            {
                return GetMonth();
                break;
            };
            case TimeType.YEAR:
            {
                return GetYear();
                break;
            };
        };
        return -1;
    };

    void GetYearMonthDayHourMinuteSecondUTC(out int year, out int month, out int day, out int hour, out int minute, out int second) 
    {
       year = m_Year;
       month = m_Month;
       day = m_Day;
       hour = m_Hour;
       minute = m_Minute;
       second = m_Second;
    };

    /**
     * @brief Mimic sprintf(,"%0*d",decaimal,width).
     * 
     * @param str 
     * @param value 
     * @param width 
     */
    static void Sprintf0d(out string str, int value, int width)
    {
        int d = value;
        if (d < 0)
        {
            str += "-";
            d = -d;
            width--;
        }
        int n = 10;
        for (int i = 2; i < width; i++)
        {
            n *= 10;
        }
        for (int i = 1; i < width && d < n; i++)
        {
            str += "0";
            n /= 10;
        }
        str += d.ToString();
    };

    /**
     * @brief Converts this Date object to a String of the form:
     *
     *                         MM DD hh:mm:ss YYYY
     * 
     * @return a string representation of this date.
     */
    string toString()
    {
        //"MM DD hh:mm:ss YYYY";

        DataTime date = Now();
        string result = "";
        
        Sprintf0d(result,date.GetMonth(),2);
        result += " ";

        Sprintf0d(result,date.GetDay(),2);
        result += " ";

        Sprintf0d(result,date.GetHour(),2);
        result += ":";

        Sprintf0d(result,date.GetMinute(),2);
        result += ":";

        Sprintf0d(result,date.GetSecond(),2);

        result += " " + date.GetYear().ToString();
        
        return result;
    };

    /**
     * @brief Converts this Date object to a String of the form:
     *
     *                         YYYY.MM.DD-hh.mm.ss
     * 
     * @return a string representation of this date.
     */
    string toString1()
    {
        //"YYYY.MM.DD-hh.mm.ss";

        DataTime date = Now();
        string result = "";

        result += date.GetYear().ToString() + ".";
        
        Sprintf0d(result,date.GetMonth(),2);
        result += ".";

        Sprintf0d(result,date.GetDay(),2);
        result += ".";

        Sprintf0d(result,date.GetHour(),2);
        result += ".";

        Sprintf0d(result,date.GetMinute(),2);
        result += ".";

        Sprintf0d(result,date.GetSecond(),2);
        
        return result;
    };
};