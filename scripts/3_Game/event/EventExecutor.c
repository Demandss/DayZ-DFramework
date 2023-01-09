/*
 This code powered by ©Demands.
 at 11/09/2023
 */

class DEventExecutor
{
    string function;

    void DEventExecutor(string _function)
    {
        this.function = _function;
    }

    void Execute(Listener listener, DEvent devent)
    {
        GetGame().GameScript.CallFunction( listener, this.function, NULL, devent );
    }
}