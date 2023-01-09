class TimeUtility 
{
    static const int EPOCH_YEAR = 1970;
    static const int EPOCH_MONTH = 1;
    static const int EPOCH_DAY = 1;

    static const int MILLIS_CENTURY = 3153600000000;
    static const int MILLIS_YEAR = 31536000000;
    static const int MILLIS_MOUNTH = 2592000000;
    static const int MILLIS_WEEK = 604800000;
    static const int MILLIS_DAY = 86400000;
    static const int MILLIS_HOUR = 3600000;
    static const int MILLIS_MINUTE = 60000;
    static const int MILLIS_SECOND = 1000;

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

    private static int CalculateYMDToMillis(int year, int month, int day)
    {
        int time;

        for (int iYear = EPOCH_YEAR; iYear < year; iYear++)
        {
            if (IsLeapYear(iYear))
            {
                time += MILLIS_YEAR + MILLIS_DAY;
            }
            else
            {
                time += MILLIS_YEAR;
            }
        };

        bool isLeapYear = IsLeapYear(year);

        for (int iMonth = EPOCH_MONTH; iMonth < month; iMonth++)
        {
            if (isLeapYear && iMonth == 2)
            {
                time += MILLIS_DAY;
            }
            time += DAYS_IN_MONTH[iMonth - 1] * MILLIS_DAY;
        };

        for (int iDay = EPOCH_DAY; iDay < day; iDay++)
        {
            time += MILLIS_DAY;
        };

        return time;
    };

    /**
     * @brief 
     * 
     * @return Current world time in milliseconds.
     */
    static int CurrenWorldTimeMillis()
    {
        int year;
		int month;
		int day;

		int hour;
		int minute;
        
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);

        int time;

        time += CalculateYMDToMillis(year,month,day);
        time += hour * MILLIS_HOUR;
        time += minute * MILLIS_MINUTE;

        return time;
    }

    /**
     * @brief 
     * 
     * @return the difference, measured in milliseconds, 
     * between the current time and midnight, January 1, 1970 UTC.
     */
    static int CurrentTimeMillis()
    {
        int year;
        int month;
        int day;

        int hour;
        int minute;
        int second;

        DataTime data = new DataTime();
        data.GetYearMonthDayHourMinuteSecondUTC(year,month,day,hour,minute,second);

        int time;

        time += CalculateYMDToMillis(year,month,day);
        time += hour * MILLIS_HOUR;
        time += minute * MILLIS_MINUTE;
        time += second * MILLIS_SECOND;

        return time;
    };

    /**
     * @brief turns milliseconds into a string with time.
     * 
     * @param milliseconds 
     * @return "10 seconds 20 minutes 234 years"
     */
    static string TimeConverter(int seconds)
    {
        const array<string> words = {
            "#timeform_second_type_","#timeform_minute_type_",
            "#timeform_hour_type_","#timeform_day_type_",
            "#timeform_week_type_","#timeform_month_type_",
            "#timeform_year_type_","#timeform_century_"
        }; 
        const array<int> time = {
            MILLIS_CENTURY, MILLIS_YEAR,
            MILLIS_MOUNTH, MILLIS_WEEK, 
            MILLIS_DAY, MILLIS_HOUR, 
            MILLIS_MINUTE, 1
        };
        
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

    static string CurrentTimeByMask(TimeMask mask)
    {
        return TimeByMask(mask,new DataTime());
    };

    static string TimeByMask(TimeMask mask, DataTime time)
    {
        bool masked = false;
        string selectedMask = "";
        map<TimeType, string> timeDeterminants = new map<TimeType, string>;

        if (mask == TimeMask.TIME)
        {
            selectedMask = TIME_MASK;
            timeDeterminants.Insert(TimeType.HOUR,"hh");
            timeDeterminants.Insert(TimeType.MINUTE,"mm");
            timeDeterminants.Insert(TimeType.SECOND,"ss");
            masked = true;
        }
        if (!masked && mask == TimeMask.DATE)
        {
            selectedMask = DATE_MASK;
            timeDeterminants.Insert(TimeType.YEAR,"YYYY");
            timeDeterminants.Insert(TimeType.MONTH,"MM");
            timeDeterminants.Insert(TimeType.DAY,"DD");
            masked = true;
        }
        if (!masked && mask == TimeMask.DATETIME)
        {
            selectedMask = DATETIME_MASK;
            timeDeterminants.Insert(TimeType.YEAR,"YYYY");
            timeDeterminants.Insert(TimeType.MONTH,"MM");
            timeDeterminants.Insert(TimeType.DAY,"DD");
            timeDeterminants.Insert(TimeType.HOUR,"hh");
            timeDeterminants.Insert(TimeType.MINUTE,"mm");
            timeDeterminants.Insert(TimeType.SECOND,"ss");
        }
        return TimeByCustomMask(selectedMask, timeDeterminants, time);
    };

    static string TimeByCustomMask(string mask, map<TimeType, string> determinants, DataTime time) 
    {
        string result = mask;
        array<TimeType> timeType = {TimeType.SECOND,TimeType.MINUTE,TimeType.HOUR,TimeType.DAY,TimeType.MONTH,TimeType.YEAR};
        
        foreach(TimeType type: timeType)
        {
            if (determinants.Contains(type))
            {
                result.Replace(determinants.Get(type),time.GetTimeByType(type).ToString());
            }
        }
        return result;
    };
};
