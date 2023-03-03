class ModificationBase extends Modification
{
    override string GetName() 
    {
        if (this.GetDescription() != NULL)
            return this.GetDescription().GetName();
        else
            return "";
    };

    int HashCode() 
    {
        return this.GetName().Hash();
    };
};