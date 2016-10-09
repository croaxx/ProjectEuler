namespace FleesDistribution
{
   public class FleeProbabilityDistribution<Field> where Field : IField
   {
      public IField _field { get; private set; }
      public FleeProbabilityDistribution(Field grid, uint i, uint j)
      {
         _field = grid;
         _field[i, j] = 1.0m;
      }

      public void CalcDistributionAfterBells(uint bellRings)
      {
         for (uint i = 0; i < bellRings; i++)
         {
            FleeJumpEvaluation();
         }
      }

      private void FleeJumpEvaluation()
      {
         var newProbabilityMatrix = _field.CreateNewZeroField();

         for (uint i = 0; i < _field.GetSize(); i++)
         {
            for (uint j = 0; j < _field.GetSize(); j++)
            {
               var valueAtPoint = _field[i, j];
               if (valueAtPoint != (decimal)0.0)
               {
                  MakeJumps(newProbabilityMatrix, i, j, valueAtPoint * GetProbabilityMultiplyer(i, j));
               }
            }
         }
         _field = newProbabilityMatrix;
      }

      private void MakeJumps(IField matrix, uint i, uint j, decimal valueToAdd)
      {
         // Vertical jump
         if (i == 0)
         {
            matrix[i + 1, j] += valueToAdd;
         }
         else if (i == _field.GetSize() - 1)
         {
            matrix[i - 1, j] += valueToAdd;
         }
         else
         {
            matrix[i + 1, j] += valueToAdd;
            matrix[i - 1, j] += valueToAdd;
         }
         // Horizontal jump
         if (j == 0)
         {
            matrix[i, j + 1] += valueToAdd;
         }
         else if (j == _field.GetSize() - 1)
         {
            matrix[i, j - 1] += valueToAdd;
         }
         else
         {
            matrix[i, j + 1] += valueToAdd;
            matrix[i, j - 1] += valueToAdd;
         }
      }

      private decimal GetProbabilityMultiplyer(uint i, uint j)
      {
         if (i == 0 || i == _field.GetSize() - 1)
         {
            if (j == 0 || j == _field.GetSize() - 1)
            {
               return 1.0m / 2.0m;
            }
            else
            {
               return 1.0m / 3.0m;
            }
         }
         else
         {
            if (j == 0 || j == _field.GetSize() - 1)
            {
               return 1.0m / 3.0m;
            }
            return 1.0m / 4.0m;
         }
      }
      public uint GetSize()
      {
         return _field.GetSize();
      }
   }
}
