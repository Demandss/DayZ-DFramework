/*
 This code powered by ©Demands.
 at 5/10/2022
 */

class FileConfigurationBase extends FileSystem
{
    const string CONFIG_FILE_PATH = "$profile:config/";
    const string CONFIG_FILE_EXTENSION = ".cfg";

    private string subFolder = "";

    void FileConfigurationBase()
    {
        if (!FileExist(CONFIG_FILE_PATH)) MakeDirectory(CONFIG_FILE_PATH);
    };

    string GetSubFolder() { return subFolder; };

    void SetSubFolder(string path)
    {
        int index = path.LastIndexOf(GetSeparator());
        if (index == -1) 
        {
            SetFileName(path);
            return;
        }
        SetFileName(path.Substring(index, path.Length()));
        subFolder = path.Substring(0,index)
    };

    override string GetDirectory() { return CONFIG_FILE_PATH + subFolder; }
    
    override void SetFilename(string name) 
    {
        int index = name.LastIndexOf(".");
        if (index == -1)
        {
            filename = name;
            extension = CONFIG_FILE_EXTENSION;
            return;
        }
        extension = name.Substring(index, name.Length() - index);
        filename = name.Substring(0,name.Length() - extension.Length());
        extension = CONFIG_FILE_EXTENSION;
    };
};