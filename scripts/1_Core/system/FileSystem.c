/*
 This code powered by ©Demands.
 at 4/22/2022
 */

class FileSystem
{
    private static string SEPARATOR = "/";
    private static string ALT_SEPARATOR = "\\";
    private static string SEMICOLON = ";";

    protected string directory;
    protected string filename;
    protected string extension;

    static bool IsSlash(string s) { return (s == ALT_SEPARATOR) || (s == SEPARATOR); };

    static string GetSeparator() { return SEPARATOR; };

    static string GetPathSeparator() { return SEMICOLON; };

    string GetFileName() { return filename; };
	
    string GetExtension() { return extension; };

    string GetFullFileName() { return filename + extension; };

    string GetDirectory() { return directory; };

    string GetPath() { return GetDirectory() + GetFullFileName(); };

    void SetFileName(DString name)
    {
		//is a temporary line until they fix this method themselves | 09/02/2022
		int index = name.dLastIndexOf(".");

        //int index = name.LastIndexOf(".");
        if (index == -1)
        {
            filename = name;
            extension = "";
            return;
        }
        extension = name.Substring(index, name.Length() - index);
        filename = name.Substring(0,name.Length() - extension.Length());
    };

    void SetDirectory(string path) { directory = path; };

	/**
	 * @brief Retrieves a directory from a path to a file
	 */
    string GetDirectory(DString path) 
    { 
        path.Replace(ALT_SEPARATOR, GetSeparator());

        int index = path.dLastIndexOf(GetSeparator());

        if (index != -1)
            return path.Substring(0,index) + GetSeparator();

        return string.Empty;
    };

	void GenerateDirectory(DString path = string.Empty)
    {
		DString dir;
		TStringArray folders = new TStringArray;

		if (path == string.Empty)
			dir = GetDirectory();
		else
			dir = GetDirectory(path);

		if (dir.dCountChar(GetSeparator()) <= 1)
		{
			if (!FileExist(dir)) MakeDirectory(dir);
			return;
		}

		dir.Split(GetSeparator(),folders);

		string _folder = string.Empty;

		foreach (string folder : folders)
		{
			string f_folder = _folder + GetSeparator() + folder;
			if (!FileExist(f_folder)) 
			{
				MakeDirectory(f_folder);
			}
			_folder += folder + GetSeparator();
		}
    };

	/**
	 * @brief Gives the found files in the given directory, taking into account the search flag
	 * 
	 * @return Got it or not
	 */
    static bool GetFiles(DString path, out array<DFile> files, FindFileFlags flag = FindFileFlags.ALL)
	{
		if (!files) files = new array<DFile>();

		path.Replace("\\", GetSeparator());

		string fileName;
		FileAttr fileAttr;
		string folder;
		FindFileHandle handle = FindFile(path, fileName, fileAttr, flag);
		if (!handle) return false;

		path.Replace(ALT_SEPARATOR, GetSeparator());

        int index = path.dLastIndexOf(GetSeparator());

        if (index != -1)
            folder = path.Substring(0,index) + GetSeparator();
		else
			folder = string.Empty;

		while (true)
		{
			DFile file = new DFile();
			file.SetFileName(fileName);
			file.SetDirectory(folder);
			file.SetAttributes(fileAttr);

			files.Insert(file);
            
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
	static void CreateFile(DString path)
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
	static FileHandle RecreateFile(DString path)
	{
		if(FileExist(path))
		{
			DeleteFile(path);			
		}
		return OpenFile(path, FileMode.WRITE);
	};
};