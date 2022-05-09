class DataTime
{
    protected int m_Year;
    protected int m_Month;
    protected int m_Day;
    protected int m_Hour;
    protected int m_Minute;
    protected int m_Second;

    void DataTime()
    {        
        GetYearMonthDayUTC(m_Year,m_Month,m_Day);
        GetHourMinuteSecondUTC(m_Hour,m_Minute,m_Second);
    };

    int GetYear() {return m_Year;};
    int GetMonth() {return m_Month;};
    int GetDay() {return m_Day;};
    int GetHour() {return m_Hour;};
    int GetMinute() {return m_Minute;};
    int GetSecond() {return m_Second;};

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
        for (int j = 1; j < width && d < n; j++)
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
    string ToString1()
    {
        //"MM DD hh:mm:ss YYYY";

        string result = "";
        
        Sprintf0d(result,GetMonth(),2);
        result += " ";

        Sprintf0d(result,GetDay(),2);
        result += " ";

        Sprintf0d(result,GetHour(),2);
        result += ":";

        Sprintf0d(result,GetMinute(),2);
        result += ":";

        Sprintf0d(result,GetSecond(),2);

        result += " " + GetYear().ToString();
        
        return result;
    };

    /**
     * @brief Converts this Date object to a String of the form:
     *
     *                         YYYY.MM.DD-hh.mm.ss
     * 
     * @return a string representation of this date.
     */
    string ToString2()
    {
        //"YYYY.MM.DD-hh.mm.ss";

        string result = "";

        result += GetYear().ToString() + ".";
        
        Sprintf0d(result,GetMonth(),2);
        result += ".";

        Sprintf0d(result,GetDay(),2);
        result += ".";

        Sprintf0d(result,GetHour(),2);
        result += ".";

        Sprintf0d(result,GetMinute(),2);
        result += ".";

        Sprintf0d(result,GetSecond(),2);
        
        return result;
    };
};