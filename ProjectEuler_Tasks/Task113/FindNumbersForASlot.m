function y = FindNumbersForASlot(grid,i,j,divisions)

rowSize = divisions*divisions;
rowElem = grid((i - 1)*rowSize + find(grid((i - 1)*rowSize + 1:i*rowSize)));
colElem = grid(j - rowSize + rowSize*find(grid(j:rowSize:end)));

grid_ = reshape(grid,[rowSize,rowSize])';
SubMatrix = grid_(divisions*(floor((i - 1)/divisions)) + 1:divisions*(floor((i - 1)/divisions))...
    + divisions,divisions*(floor((j - 1)/divisions)) + 1:divisions*(floor((j - 1)/divisions)) + divisions);

SubMatrixElemnts = SubMatrix(SubMatrix~=0)';

candidates = 1:divisions^2;
existingElements = zeros(1,divisions^2);
existingElements([rowElem colElem SubMatrixElemnts]) = 1;

y = candidates(xor(ones(1,divisions^2),existingElements));

end
