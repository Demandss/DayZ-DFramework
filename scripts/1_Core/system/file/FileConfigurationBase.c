/*
 This code powered by ©Demands.
 at 5/10/2022
 */

class FileConfigurationBase extends FileSystem
{
    const string CONFIG_FILE_PATH = "$profile:config/";
    const string STANDART_CONFIG_FILE_EXTENSION = ".cfg";

    private static string subFolder = "";

    void FileConfigurationBase()
    {
        if (!FileExist(CONFIG_FILE_PATH)) MakeDirectory(CONFIG_FILE_PATH);
    };

    string GetSubFolder() { return subFolder; };

    void SetSubFolder(DString path)
    {
        int index = path.dLastIndexOf(GetSeparator());
        if (index == -1) 
        {
            SetFileName(path);
            return;
        }
        SetFileName(path.Substring(index+1, path.Length() - (index+1)));
        subFolder = path.Substring(0,index+1);
    };

    override string GetDirectory() { return CONFIG_FILE_PATH + subFolder; }
    
    override void SetFileName(DString name) 
    {
        //is a temporary line until they fix this method themselves | 09/02/2022
		int index = name.dLastIndexOf(".");

        //int index = name.LastIndexOf(".");
        if (index == -1)
        {
            filename = name;
            extension = STANDART_CONFIG_FILE_EXTENSION;
            return;
        }
        extension = name.Substring(index, name.Length() - index);
        filename = name.Substring(0,name.Length() - extension.Length());
    };
};