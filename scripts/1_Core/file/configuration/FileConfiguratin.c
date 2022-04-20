/*
 This code powered by ©Demands.
 at 4/19/2022
 */

static const string CONFIG_FILE_PATH = "$profile:Configurations";

class FileConfiguratin
{
    private static FileConfiguratinBinary _FileConfigBinary;
    private static FileConfiguratinJSON _FileConfigJSON;

    /**
     * @brief To crate banyr config
     * 
     * @return FileConfiguratinBinary 
     */
    static FileConfiguratinBinary Binary(string filename)
    {
        // return _FileConfigBinary ? _FileConfigBinary : _FileConfigBinary = new FileConfiguratinBinary();
        if (!_FileConfigBinary) _FileConfigBinary = new FileConfiguratinBinary(filename);
        return _FileConfigBinary;
    };

    /**
     * @brief To crate JSON config
     * 
     * @return FileConfiguratinJSON 
     */
    static FileConfiguratinJSON JSON()
    {
        if (!_FileConfigJSON) _FileConfigJSON = new FileConfiguratinJSON(filename);
        return _FileConfigJSON;
    };
};

class FileConfiguratinBase
{
    protected filename;

    
}

class FileConfiguratinBinary extends FileConfiguratinBase
{
    protected filename;

    void FileConfiguratinBinary(string configFileName) { super(configFileName); };
}

class FileConfiguratinJSON extends FileConfiguratinBase
{

}