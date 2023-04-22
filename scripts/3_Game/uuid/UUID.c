/*
 This code powered by ©Demands.
 at 04/10/2023
 */

class UUID
{
    private const static string m_Pattern = "xxxxxxxx-xxxx-Vxxx-xxxx-xxxxxxxxxxxx";

    static string RandomUUIDv4()
    {
        string hexValues = "0123456789abcdef";
        string uuid = m_Pattern;
        uuid.Replace("V","4");

        for (int i = 0; i < 36; i++)
        {
            if (uuid[i] == "x")
                uuid[i] = hexValues.Substring(Math.Floor(Math.RandomFloat(0,16)), 1);
        }

        int N = (uuid[19]).ToInt();
        N &= 0x3;
        N |= 0x8;
        uuid[19] = hexValues.Substring(N, 1);

        return uuid;
    }
};