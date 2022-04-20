enum TimeMask
{
    TIME,
    DATE,
    DATETIME
}

enum TimeType
{
    SECOND,
    MINUTE,
    HOUR,
    DAY,
    MONTH,
    YEAR
}

class TimeUtility 
{
    static const int EPOCH_YEAR = 1970;
    static const int EPOCH_MONTH = 1;
    static const int EPOCH_DAY = 1;

    static const int SECOND_CENTURY = 3153600000;
    static const int SECOND_YEAR = 31536000;
    static const int SECOND_MOUNTH = 2592000;
    static const int SECOND_WEEK = 604800;
    static const int SECOND_DAY = 86400;
    static const int SECOND_HOUR = 3600;
    static const int SECOND_MINUTE = 60;

    static const int DAYS_IN_MONTH[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    static const string TIME_MASK = "hh:mm:ss";
    static const string DATE_MASK = "YYYY-MM-DD";
    static const string DATETIME_MASK = "YYYY-MM-DD hh:mm:ss";

    static bool IsLeapYear(int year)
    {
        if (year % 400 == 0) return true;
        if (year % 100 == 0) return true;
        if (year % 4 == 0) return true;
        return false;
    }; 
    

    /**
     * @brief 
     * 
     * @return the difference, measured in milliseconds but i'm in seconds, 
     * between the current time and midnight, January 1, 1970 UTC.
     */
    static int CurrentTimeSeconds()
    {
        int year;
        int month;
        int day;

        int hour;
        int minute;
        int second;

        DataTime data = new DataTime.Now();
        GetYearMonthDayHourMinuteSecondUTC(year,month,day,hour,minute,second);

        int time;

        for (int iYear = EPOCH_YEAR; iYear < year; iYear++)
        {
            if (IsLeapYear(iYear))
            {
                time += SECOND_YEAR + SECOND_DAY;
            }
            else
            {
                time += SECOND_YEAR;
            }
        };

        bool isLeapYear = IsLeapYear(year);

        for (int iMonth = EPOCH_MONTH; iMonth < month; iMonth++)
        {
            if (isLeapYear && iMonth == 2)
            {
                time += SECOND_DAY;
            }
            time += DAYS_IN_MONTH[iMonth - 1] * SECOND_DAY;
        };

        for (int iDay = EPOCH_DAY; iDay < day; iDay++)
        {
            time += SECOND_DAY;
        };

        time += hour * SECOND_HOUR;
        time += minute * SECOND_MINUTE;
        time += hour * SECOND_HOUR;
        time += second;

        return time;
    };

    /**
     * @brief turns seconds into a string with time.
     * 
     * @param seconds 
     * @return "10 seconds 20 minutes 234 years"
     */
    static string timeConverter(int seconds)
    {
        const string[8] words = {"timeform_second_type_","timeform_minute_type_","timeform_hour_type_","timeform_day_type_","timeform_week_type_","timeform_month_type_","timeform_year_type_","timeform_century_"}; 
        const int[8] time = {SECOND_CENTURY,SECOND_YEAR,SECOND_MOUNTH,SECOND_WEEK,SECOND_DAY, SECOND_HOUR, SECOND_MINUTE,1};
        
        string result = "";
        
        for (int i = 0; i < time.Count(); i++)
        {
            int cnt = seconds / time[i];
            seconds = seconds % time[i];

            if (cnt == 0) continue;

            if (cnt % 10 > 4)
            {
                result += words[i] + "3";
            }
            else if (cnt % 10 > 1) 
            {
                result += words[i] + "2";
            }
            else if (cnt % 10 == 1)
            {
                result += words[i] + "1";
            }
            result += " ";
        }
        return result;
    };

    static string CurrentTimeByMask(string mask)
    {
        return TimeByMask(mask,DataTime.Now());
    };

    static string TimeByMask(TimeMask mask, DataTime time)
    {
        string selectedMask = "";
        map<TimeType, string> timeDeterminants = new map<TimeType, string>;

        switch (mask)
        {
            case TimeMask.TIME:
            {
                selectedMask = TIME_MASK;
                timeDeterminants.Inser(TimeType.HOUR,"hh");
                timeDeterminants.Inser(TimeType.MINUTE,"mm");
                timeDeterminants.Inser(TimeType.SECOND,"ss");
                break;
            };
            case TimeMask.DATE:
            {
               selectedMask = DATE_MASK;
               timeDeterminants.Inser(TimeType.YEAR,"YYYY");
               timeDeterminants.Inser(TimeType.MONTH,"MM");
               timeDeterminants.Inser(TimeType.DAY,"DD");
            break;
            };
            case TimeMask.DATETIME:
            {
               selectedMask = DATETIME_MASK;
               timeDeterminants.Inser(TimeType.YEAR,"YYYY");
               timeDeterminants.Inser(TimeType.MONTH,"MM");
               timeDeterminants.Inser(TimeType.DAY,"DD");
               timeDeterminants.Inser(TimeType.HOUR,"hh");
               timeDeterminants.Inser(TimeType.MINUTE,"mm");
               timeDeterminants.Inser(TimeType.SECOND,"ss");
            break;
            };
        };

        return TimeByCustomMask(selectedMask, separator, time);
    };

    static string TimeByCustomMask(string mask, map<TimeType, string> determinants, DataTime time) 
    {
        string result = mask;
        array<TimeType> timeType = {TimeType.SECOND,TimeType.MINUTE,TimeType.HOUR,TimeType.DAY,TimeType.MONTH,TimeType.YEAR};
        
        foreach(TimeType type: timeType)
        {
            if (determinants.Contains(type))
            {
                result.Replace(determinants.Get(type),time.GetTimeByType(type));
            }
        }
        return result;
    };
};

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
    }

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
    }
};

