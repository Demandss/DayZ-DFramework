/*
 This code powered by ©Demands.
 at 4/22/2022
 */

class FileSystem
{
    private string SEPARATOR = "/";
    private string ALT_SEPARATOR = "\\";
    private string SEMICOLON = ";";

    bool IsSlash(string s) { return (s == ALT_SEPARATOR) || (s == SEPARATOR);};

    string GetSeparator() { return SEPARATOR;};

    string GetPathSeparator() { return SEMICOLON;};

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
};