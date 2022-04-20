class DFile
{
    protected string directory;
    protected string filename;
    protected string extension;

    

    void DFile(string path = "")
    {
        if (path == string.Empty) return;

        string fileName;
        FileAttr fileAttr;

        FindFileHandler handler = FindFile(path,fileName,fileAttr, FindFileFlags.ALL);

        if (!handler) return;

        SetFilename(fileName);
        
        CloseFindFile(handler);
    };

    string GetDirectory() { return directory; };

    string GetFilename() { return filename; };

    string GetExtension() { return extension; };

    void SetDirectory(string path) {directory = path; };

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
};