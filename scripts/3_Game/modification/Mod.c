class Mod
{
    void Mod(typename main, string modName)
    {
        DFramework.GetModificationManager().LoadModification(main,modName);
    };
};