using System;
using System.Collections.Generic;
using System.Linq;
namespace FleesDistribution
{
   public static class ExpectationValueEvaluator
   {
      public static decimal Calculate(List<FleeProbabilityDistribution<RectangularGrid>> assembly)
      {
         decimal expectValue = 0.0m;
         var size = assembly.First().GetSize();

         for (uint i = 0; i < size; i++)
         {
            for (uint j = 0; j < size; j++)
            {
               decimal tempValue = 1.0m;
               foreach (var flee in assembly)
               {
                  tempValue *= (1 - flee._field[i, j]);
               }
               expectValue += tempValue;
            }
         }

         return expectValue;
      }
   }
}
