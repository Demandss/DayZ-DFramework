class Modification
{
    string GetName();

    ref ModificationDescription GetDescription();

    void OnInit();

    void OnMissionPreInit();

    void OnMissionInit();

    void OnMissionPostInit();
};