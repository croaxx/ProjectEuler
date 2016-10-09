using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace FleesDistribution
{
    public class MainApplication
    {
        static void Main(string[] args)
        {
            // Input parameters (grid size and number of bell rings)   //
            const uint gridSize = 30;
            const uint bells = 50;
            //---------------------------------------------------------//

            // start the timer
            Stopwatch sw = new Stopwatch();
            sw.Start();

            // Create an assembly (list) of flea objects on a rectangular grid
            var fleaAssembly = new List<FleeProbabilityDistribution<RectangularGrid>>();
            for (uint i = 0; i < gridSize; i++)
            {
                for (uint j = 0; j < gridSize; j++)
                {
                    fleaAssembly.Add(new FleeProbabilityDistribution<RectangularGrid>(new RectangularGrid(gridSize), i, j));
                }
            }

            // Calculate probability distribution after ring of bells for each flea
            foreach (var flee in fleaAssembly)
            {
                flee.CalcDistributionAfterBells(bells);
            }

            // Get the expectation value of free blocks
            var expectationValue = ExpectationValueEvaluator.Calculate(fleaAssembly);
            sw.Stop();

            Console.WriteLine("The expected number of unoccupied blocks is: {0}", expectationValue);
            Console.WriteLine("Elapsed time={0}", sw.Elapsed);
            Console.ReadKey();
        }
    }
}
