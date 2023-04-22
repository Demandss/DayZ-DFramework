/*
 This code powered by ©Demands.
 at 09/02/2022
 */

typedef array<DString> TDStringArray;
typedef string DString;

class DString : string
{
    /** Deprecated
	 * @brief In general, it does everything the same as the one 
     *       that is originally in the game, BUT mine works, 
     *       unlike what the game provides.
     *       The function did not work from 2020 to 2023
	 */
    int dLastIndexOf(string sample)
    {
        int index = value.Length() - 1;
        while ( index >= 0 )
        {
            if(value.Get(index) == sample) return index;
            index--;
        }
        return -1;
    };

    /**
    *   @brief returns the count of a specific character in a string
    */
    int dCountChar(string sample)
    {
        int count = 0;
		for (int index = 0; index < value.Length(); index++)
		{
			count += value.Get(index) == sample;
		}
		return count;
    };

    string ReplaceInRange(int start, int len, string replacement)
    {
        autoptr array<string> arr = new array<string>;
        value.Split(value.Substring(start,len),arr);
        return arr[0] + replacement + arr[1];
    };
};