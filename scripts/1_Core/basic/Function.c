/*
 This code powered by ©Demands.
 at 12/28/2023
 */

class Function
{
    protected string name;
    protected Class parent;

    void Function(string _name, Class _parent)
    {
        this.name = _name;
        this.parent = _parent;
    }

    string GetName() { return this.name; };

    Class GetParent() { return this.parent; };
}