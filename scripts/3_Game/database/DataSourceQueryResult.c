class DataSourceQueryResult
{
    private ref map<string,ref array<string>> m_Data = new map<string,ref array<string>>;
    private int m_Iterator = -1;
    private int m_IteratorEnd = -1;

    void DataSourceQueryResult(string data)
    {
        auto result = new map<string,array<string>>;
		JsonSerializer serializer = new JsonSerializer;
        string error;
        if (!serializer.ReadFromString(result, data, error))
            GetDFLogger().Error("Looks like the following error occurred while reading the data :: " + error);

        m_Data.Copy(result);

        if (m_Data != NULL)
            m_IteratorEnd = ((m_Data.GetElement(0)).Count() - 1);
    };

    int GetColumnCount()
    {
        return m_Data.Count();
    };

    ref array<string> GetColumnNames()
    {
        return m_Data.GetKeyArray();
    };

    /**
     * @brief Moves the cursor forward one row from its current position. 
     *        A ResultSet cursor is initially positioned before the first row; 
     *        the first call to the method next makes the first row the current row; 
     *        the second call makes the second row the current row, and so on.
     *        When a call to the next method returns false, the cursor is positioned -1.
     */
    bool Next()
    {
        if (m_IteratorEnd == -1)
            return false;

        m_Iterator += 1;
        if (m_Iterator > m_IteratorEnd)
        {
            m_IteratorEnd == -1;
            return false;
        }
        return true;
    };

    ref array<string> GetColumn(int columnIndex)
    {
        return m_Data.GetElement(columnIndex);
    };

    string GetString(int columnIndex)
    {
        return GetColumn(columnIndex).Get(m_Iterator);
    };

    bool GetBoolean(int columnIndex)
    {
        string data = GetString(columnIndex);
        return (data.Trim() == "true" || data.ToInt() == 1);
    };

    int GetInt(int columnIndex)
    {
        return GetString(columnIndex).ToInt();
    };

    float GetFloat(int columnIndex)
    {
        return GetString(columnIndex).ToFloat();
    };

    vector GetVector(int columnIndex)
    {
        string data = GetString(columnIndex);
        data.Replace("<","");
        data.Replace(">","");
        data.Replace(",","");
        return data.ToVector();
    };

    /**
     * @brief I'm not sure if this will work, I wrote when I was sick
     * @return DataTime 
     */
    ref DataTime GetDataTime(int columnIndex)
    {
        return convertStrToDataTime(GetString(columnIndex));
    };

    ref array<string> GetColumn(string columnName)
    {
        return m_Data.Get(columnName);
    };

    string GetString(string columnName)
    {
        return GetColumn(columnName).Get(m_Iterator);
    };

    bool GetBoolean(string columnName)
    {
        string data = GetString(columnName);
        return (data.Trim() == "true" || data.ToInt() == 1);
    };

    int GetInt(string columnName)
    {
        return GetString(columnName).ToInt();
    };

    float GetFloat(string columnName)
    {
        return GetString(columnName).ToFloat();
    };

    vector GetVector(string columnName)
    {
        string data = GetString(columnName);
        data.Replace("<","");
        data.Replace(">","");
        data.Replace(",","");
        return data.ToVector();
    };

    /**
     * @brief I'm not sure if this will work, I wrote when I was sick
     * @return DataTime 
     */
    ref DataTime GetDataTime(string columnName)
    {
        return convertStrToDataTime(GetString(columnName));
    };

    private DataTime convertStrToDataTime(string data)
    {
        if (data.Length() == 4 || data.Length() == 2)
            return new DataTime(data.ToInt());

        if (data.Contains(" "))
        {
            TStringArray arr = new TStringArray;
            data.Split(" ",arr);
            if (arr.Count() == 2)
            {
                TStringArray arr1 = new TStringArray;
                TStringArray arr2 = new TStringArray;
                if (arr[0].Contains("-"))
                    arr[0].Split("-",arr1);
                if (arr[1].Contains(":"))
                    arr[1].Split(":",arr2);

                DataTime data1;
                DataTime data2;
                if (arr1.Count() != 0)
                    data1 = new DataTime(arr1[0].ToInt(),arr1[1].ToInt(),arr1[2].ToInt(),0,0,0);
                if (arr2.Count() != 0)
                    data2 = new DataTime(0,0,0,arr2[0].ToInt(),arr2[1].ToInt(),arr2[2].ToInt());

                return new DataTime(data1.GetYear(),data1.GetMonth(),data1.GetDay(),data1.GetHour(),data1.GetMinute(),data1.GetSecond());
            }
        }
        
        return NULL;
    }; 
};