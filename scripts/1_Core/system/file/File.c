/*
 This code powered by ©Demands.
 at 4/22/2022
 */

class DFile extends FileSystem
{
    protected FileAttr attributes;
    
    void DFile(DString path = "")
    {
        if (path == DString.Empty) return;

        DString dir = GetDirectory(path);

        GenerateDirectory(dir);

        string fileName;
        FileAttr fileAttr;

        FindFileHandle handler = FindFile(path,fileName,fileAttr, FindFileFlags.ALL);
        
        if (!handler) 
        {
            this.CreateFile(path);
            handler = FindFile(path,fileName,fileAttr, FindFileFlags.ALL);
        }

        this.SetFileName(fileName);
        this.SetAttributes(fileAttr);
        this.SetDirectory(dir);
        
        CloseFindFile(handler);
    };

    bool IsDirectory() { return (attributes & FileAttr.DIRECTORY) != 0; };

    bool IsHidden() { return (attributes & FileAttr.HIDDEN) != 0;};

    bool IsReadOnly() { return (attributes & FileAttr.READONLY) != 0;};

    bool IsValid() { return (attributes & FileAttr.INVALID) != 0;};

    void SetAttributes(FileAttr attr) { attributes = attr;};

    FileHandle OpenDFile(FileMode mode)
    {
        return OpenFile(GetPath(), mode);
    };

    void Print(string var)
    {
        FileHandle file = OpenDFile(FileMode.WRITE);
        if (file == 0)
        {
            GetLogger().Warning(string.Format("Failed to write data to the file /%1/ it may be corrupted!",GetPath()));
            return;
        }

        FPrint(file, var);
		CloseFile(file);
    };

    void Println(string var)
    {
        FileHandle file = OpenDFile(FileMode.WRITE);
        if (file == 0)
        {
            GetLogger().Error(string.Format("Failed to write data to the file /%1/ it may be corrupted!",GetPath()));
            return;
        }

        FPrintln(file, var);
		CloseFile(file);
    };

    int Read(out array<string> param_array, int length)
    {
        FileHandle file = OpenDFile(FileMode.READ);
        if (file == 0)
        {
            GetLogger().Error(string.Format("Failed to read data from the file /%1/ it may be corrupted!",GetPath()));
            return -1;
        }

        return ReadFile(file,param_array,length);
    };

    ref array<string> ReadAll()
    {
        FileHandle file = OpenDFile(FileMode.READ);
        if ( file == 0 )
        {
            GetLogger().Error(string.Format("Failed to read data from the file /%1/ it may be corrupted!",GetPath()));
            return NULL;
        }

        string line_content;
        ref array<string> file_content = new array<string>;

        while ( FGets( file,  line_content ) >= 0 )
        {
            file_content.Insert(line_content);
        }

        return file_content;
    }

    bool Rename(string name)
    {
        if (!IsValid()) return false;

        if (FileExist(directory + name) || !CopyFile(GetPath(), directory + name))
        {
            GetLogger().Error(string.Format("File already exists at /%1/",GetDirectory()));
            return false;
        }
    
        if (!DeleteFile(GetPath()))
            GetLogger().Warning(string.Format("Failed to delete original file /%1/ to rename!",GetPath()));

        SetFileName(name);

        return true;
    };

    bool MoveTo(string path)
    {
        if (!IsValid()) return false;

        if (FileExist(path + filename) || !CopyFile(GetPath(), path + filename))
        {
            GetLogger().Error(string.Format("File already exists at /%1/",path));
            return false;
        }

        if (!DeleteFile(GetPath()))
            GetLogger().Warning(string.Format("Failed to delete original file /%1/ to move!",GetPath()));

        SetFileName(filename);
        SetDirectory(path);

        return true;
    };

    bool Copy(string path)
    {
        if (!IsValid()) return false;

        if (FileExist(path + filename) || !CopyFile(GetPath(), path + filename))
        {
            GetLogger().Error(string.Format("File already exists at /%1/",path));
            return false;
        }

        SetDirectory(path);

        return true;
    };

    override string GetDebugName()
    {
        return string.Format("{path=%1;filename=%2;directory=%3;hidden=%4;readonly=%5;valid=%6}",GetPath(),GetFileName(),GetDirectory(),IsHidden(),IsReadOnly(),IsValid());
    };

    override static bool GetFiles(DString path, out array<DFile> files, FindFileFlags flag = FindFileFlags.ALL)
	{
        GetLogger().Warning("You can't get a list of files from DFile!");
        return false;
    }
};