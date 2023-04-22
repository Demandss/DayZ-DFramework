/*
 This code powered by ©Demands.
 at 04/12/2023
 */

/**
 * @brief Derivate from this class if you want to calculate odds for custom classes;
 *        Example:
 *          class CustomItem extends Chanceble
 *          {
 *              float m_Chance = 0.2;
 *              
 *              float GetChance()
 *              {
 *                  return m_Chance;
 *              };
 *          };
 *          class CustomItem1 extends Chanceble
 *          {
 *              float m_Chance = 0.5;
 *              
 *              float GetChance()
 *              {
 *                  return m_Chance;
 *              };
 *          };
 *          
 *          a function in which you want to get an item by chance:
 *          void func() 
 *          {
 *              array<ref Chanceble> arr = {new CustomItem(),new CustomItem1()};
 *              
 *              Chanceble winer = ChanceCalculatorUtility.Calculate(arr);
 *          }
 */
class Chanceble
{
    float GetChance();
};

class ChanceCalculatorUtility
{
    /**
     * @brief for get a certain number of winners items by chance
     * 
     * @param data - сhanceble items arr
     * @param amount
     * @return arr winers by amount
     */
    static ref array<ref Chanceble> CalculateSpecificAmount(array<Chanceble> data, int amount)
    {
        autoptr array<ref Chanceble> result = new array<ref Chanceble>;
        
        for (int i = 0; i < amount; i++)
        {
            result.Insert(Calculate(data));
        }

        return result;
    }

    /**
     * @brief for get a winner item by chance
     * 
     * @param data - сhanceble items arr
     * @return winner
     */
    static ref Chanceble Calculate(array<Chanceble> data)
    {
        autoptr array<ref Chanceble> var = new array<ref Chanceble>;

        while (true)
        {
            var.Clear();
            var.Copy(data);
            var.ShuffleArray();

            float randomChance = Math.RandomFloat01();
            for (int i = 0; i < var.Count(); i++)
            {
                if (var.Get(i))
                {
                    float insideChance = var.Get(i).GetChance();
                    if (insideChance < randomChance) 
                    {
                        var.Remove(i);
                    }
                }
            }

            if (var.Count() != 0)
            {
                break;
            }
        }

        float min = var.Get(0).GetChance();
        foreach (ref Chanceble varItem : var)
        {
            float chance = varItem.GetChance();
            if (chance < min)
            {
                min = chance;
            }
        }

        autoptr array<ref Chanceble> winItems = new array<ref Chanceble>;

        foreach (ref Chanceble _varItem : var)
        {
            if (_varItem.GetChance() == 1)
            {
                return _varItem;
            }
            else if (_varItem.GetChance() == min) 
            {
                winItems.Insert(_varItem);
            }
        }

        if (var.Count() == 0) return NULL; //this should never happen but I'll leave it here just in case..

        return winItems.GetRandomElement();
    };
};