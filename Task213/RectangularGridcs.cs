namespace FleesDistribution
{
   public interface IField
   {
      uint GetSize();
      decimal this[uint i, uint j] { get; set; }
      IField CreateNewZeroField();
   }

   public class RectangularGrid : IField
   {
      private readonly uint _size;  // size of the grid
      private decimal[,] _field;    // grid

      public decimal this[uint i, uint j]
      {
         get
         {
            return _field[i, j];
         }

         set
         {
            _field[i, j] = value;
         }
      }

      public RectangularGrid(uint size)
      {
         _size = size;
         _field = new decimal[_size, _size];
      }

      public IField CreateNewZeroField()
      {
         return new RectangularGrid(_size);
      }

      public uint GetSize()
      {
         return _size;
      }
   }
}

