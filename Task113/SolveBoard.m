function y=SolveBoard(grid,divisions,numSlotElements)

% prepare the solution steps sequences and digit candidates
stepNum = 1;
[elementsAt,i_min,j_min] = FindCandidatesForTheStep(grid,divisions,numSlotElements);
treeIdx = [];

if (length(elementsAt(i_min,j_min).elems) > 1)
    treeIdx = stepNum;
end

stepSeq(stepNum).candidates = elementsAt(i_min,j_min).elems;
stepSeq(stepNum).i_min = i_min;
stepSeq(stepNum).j_min = j_min;
gridSeq(stepNum).grid = grid;

isSolved = false;
% Main solving cycle
while (~isSolved)
    % change the number in the grid corresponding to the last candidate
    gridSeq(stepNum).grid((stepSeq(stepNum).i_min - 1)*numSlotElements+stepSeq(stepNum).j_min) = stepSeq(stepNum).candidates(end);
    
    if (all(gridSeq(stepNum).grid))
        isSolved = true;
        y = gridSeq(stepNum).grid;
    else
        [elementsAt,i_min,j_min] = FindCandidatesForTheStep(gridSeq(stepNum).grid,divisions,numSlotElements);
        
        % if no element can be found go to the previus node step
        if (isempty(i_min))
            stepNum = treeIdx(end); % go to the last node step
            stepSeq(stepNum).candidates(end) = []; % remove the last candidate at this step (as it was already used)
            
            % if the number of candidates is 1, then remove the node index
            if (length(stepSeq(stepNum).candidates) == 1)
                treeIdx(end) = [];
            end
            
        else
            
            stepNum = stepNum + 1;
            stepSeq(stepNum).candidates = elementsAt(i_min,j_min).elems;
            stepSeq(stepNum).i_min = i_min;
            stepSeq(stepNum).j_min = j_min;
            
            if (length(elementsAt(i_min,j_min).elems) > 1)
                treeIdx=[treeIdx stepNum];
            end
            
            gridSeq(stepNum).grid = gridSeq(stepNum - 1).grid;
        end
        
    end
end

end