/*
 This code powered by ©Demands.
 at 11/09/2023
 */

class DEventExecutor
{
    string m_Function;

    void DEventExecutor(string _function)
    {
        this.m_Function = _function;
    }

    void Execute(Listener listener, DEvent devent)
    {
        GetGame().GameScript.CallFunction( listener, this.m_Function, NULL, devent );
    }
}