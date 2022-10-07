/*
 This code powered by ©Demands.
 at 5/10/2022
 */

class RegisterConfig<Class T>
{
    /**
    * @brief needed to register JSON configuration files example:
    *  
    *  @code
    *      [RegisterConfig<TestConfigData>.Json("test/config.json")]
    *      class TestConfigData
    *      {
    *          protected string text;
    *      
    *          void TestConfigData(string _text = "I can't even imagine what should be here")
    *          {
    *              text = _text;
    *          };
    *      
    *          string GetText()
    *          {
    *              return text;
    *          };
    *      };
    *  @endcode
    *  
    * @param fileName is a path to a file like "/folder/filename.cfg"
    */
    static void Json(string path)
    {
        JsonConfigMaker<T> configMaker = new JsonConfigMaker<T>;
        configMaker.Register(path);
    };

    /**
    * @brief needed to register JSON configuration files example:
    *  
    *  @code
    *      [RegisterConfig<TestConfigData>.Binary("test/config.cfg")]
    *      class TestConfigData
    *      {
    *          protected string text;
    *      
    *          void TestConfigData(string _text = "I can't even imagine what should be here")
    *          {
    *              text = _text;
    *          };
    *      
    *          string GetText()
    *          {
    *              return text;
    *          };
    *      };
    *  @endcode
    *  
    * @param fileName is a path to a file like "/folder/filename.cfg"
    */
    static void Binary(string path)
    {
        BinaryConfigMaker<T> configMaker = new BinaryConfigMaker<T>;
        configMaker.Register(path);
    };
};