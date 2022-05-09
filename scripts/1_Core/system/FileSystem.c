/*
 This code powered by ©Demands.
 at 4/22/2022
 */

class FileSystem
{
    private string SEPARATOR = "/";
    private string ALT_SEPARATOR = "\\";
    private string SEMICOLON = ";";

    protected string directory;
    protected string filename;
    protected string extension;

    bool IsSlash(string s) { return (s == ALT_SEPARATOR) || (s == SEPARATOR);};

    string GetSeparator() { return SEPARATOR;};

    string GetPathSeparator() { return SEMICOLON;};

    string GetFileName() { return filename; };
	
    string GetExtension() { return extension; };

    string GetFullFileName() { return filename + extension; };

    string GetDirectory() { return directory; };

    string GetPath() { return GetDirectory() + GetFullFileName(); };

    void SetFilename(string name) 
    {
        int index = name.LastIndexOf(".");
        if (index == -1)
        {
            filename = name;
            extension = "";
            return;
        }
        extension = name.Substring(index, name.Length() - index);
        filename = name.Substring(0,name.Length() - extension.Length());
    };

    void SetDirectory(string path) {directory = path; };

	/**
	 * @brief Retrieves a directory from a path to a file
	 */
    string GetDirectory(string path) 
    { 
        path.Replace(ALT_SEPARATOR, SEPARATOR);

        int index = path.IndexOf(SEPARATOR);

        if (index != -1)
            return path.Substring(0,index) + SEPARATOR;

        return string.Empty;
    };

	/**
	 * @brief Gives the found files in the given directory, taking into account the search flag
	 * 
	 * @return Got it or not
	 */
    static bool GetFiles(string path, out array<ref DFile> files, FindFileFlags flag = FindFileFlags.ALL)
	{
		if (!files) files = new array<ref DFile>();

		path.Replace("\\", SEPARATOR);

		string fileName;
		FileAttr fileAttr;
		FindFileHandle handle = FindFile(path, fileName, fileAttr, flags);
		if (!handle) return false;

		string folder = GetDirectory(path);

		while (true)
		{
			DFile file = new DFile();
			file.SetFilename(fileName);
			file.SetDirectory(folder);
			file.SetAttributes(fileAttr);

			files += file;
            
			if (!FindNextFile(handle, fileName, fileAttr)) break;
		}
		CloseFindFile(handle);
		return true;
	};

	/**
	 * @brief allows you to create a file
	 * 
	 * @param path is full path to the file
	 */
	static void CreateFile(string path)
	{
		FileHandle file = OpenFile(path, FileMode.WRITE);
		if (file == 0) return;
		CloseFile(file);
	};

	/**
	 * @brief Recreates the file by returning a FileHandle, 
	 *        don't forget to close it after use with "CloseFile"
	 * 
	 * @param path is full path to the file
	 * @return FileHandle 
	 */
	static FileHandle RecreateFile(string path)
	{
		if(FileExist(path))
		{
			DeleteFile(path);			
		}
		return OpenFile(path, FileMode.WRITE);
	};
};