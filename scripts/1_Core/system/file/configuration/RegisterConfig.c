/*
 This code powered by ©Demands.
 at 5/10/2022
 */

class RegisterJsonConfig
{
    /**
     * @brief needed to register JSON configuration files example:
     * 
     *   [RegisterJsonConfig("test/config.cfg", new TestConfigData)]
     *   class TestConfigData
     *   {
     *       protected string text;
     *
     *      void TestConfigData(string _text = "I can't even imagine what should be here")
     *      {
     *          text= _text;
     *      };
     *
     *      string GetText()
     *      {
     *          return text;
     *      };
     *  };
     *
     * @param fileName is a path to a file like "/folder/filename.cfg"
     * @param data here we pass the initialized class
     */
    void RegisterJsonConfig(string path,Class data)
    {
        JsonConfigManager.Register(path,data);  
    };
};

class RegisterBinaryConfig
{
    /**
     * @brief needed to register binary configuration files example:
     * 
     *   [RegisterBinaryConfig("test/config.cfg", new TestConfigData)]
     *   class TestConfigData
     *   {
     *       protected string text;
     *
     *      void TestConfigData(string _text = "I can't even imagine what should be here")
     *      {
     *          text= _text;
     *      };
     *
     *      string GetText()
     *      {
     *          return text;
     *      };
     *  };
     *
     * @param fileName is a path to a file like "/folder/filename.cfg"
     * @param data here we pass the initialized class
     */
    void RegisterBinaryConfig(string path,Class data)
    {
        BinaryConfigManager.Register(path,data);  
    };
};