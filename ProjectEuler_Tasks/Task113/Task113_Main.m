clc; clear; close all;
tic
divisions = 3;
numSlotElements = 9;
filePath='C:\Users\Niko\Desktop\p096_sudoku.txt';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Read grids from file
grids_=ReadGridsFromFile(filePath,numSlotElements);

%% Solve boards
parfor ii = 1:length(grids_(:,1))
    gridNum(ii).grid = SolveBoard(grids_(ii,:),divisions,numSlotElements);
end

%% Find the sum of a 3-digit number located in the top left corner
num = 0;
for ii = 1:50
    num = num + 100*gridNum(ii).grid(1) + 10*gridNum(ii).grid(2) + gridNum(ii).grid(3);
end

disp(['The sum of digits is: ',num2str(num)]);
toc