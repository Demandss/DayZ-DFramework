class ColorUtility
{
    /**
     * @brief Helps convert hex to color number format.
     * 
     * @param color - Write something like "0xFF00FFFF"
     * @return int 
     */
    static int ColorHexToInt(string color)
    {
        color.Replace("0x","");
        int alpha = 0;
        int red = 0;
        int green = 0;
        int blue = 0;

        if (color.Length() == 8)
        {
            alpha = ("0x" + color[0] + color[1]).HexToInt();
            red = ("0x" + color[2] + color[3]).HexToInt();
            green = ("0x" + color[4] + color[5]).HexToInt();
            blue = ("0x" + color[6] + color[7]).HexToInt();
        }
        else if (color.Length() >= 2)
            red = ("0x" + color[0] + color[1]).HexToInt();
        
        if (color.Length() >= 4)
            green = ("0x" + color[2] + color[3]).HexToInt();

        if (color.Length() >= 6)
            blue = ("0x" + color[4] + color[5]).HexToInt();

        return ARGB(alpha, red, green, blue);
    }
}