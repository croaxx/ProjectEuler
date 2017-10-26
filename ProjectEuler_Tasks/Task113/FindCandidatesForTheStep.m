function [elementsAt,i_min,j_min] = FindCandidatesForTheStep(grid, divisions, numSlotElements)

nRows = sqrt(length(grid));
candidates = 1e3;
elementsAt = [];
i_min = [];
j_min = [];

elementsAt(nRows,nRows).elems = [];
for ii=1:nRows
    for jj=1:nRows
        if (grid((ii - 1)*numSlotElements + jj) == 0)
            elementsAt(ii,jj).elems = FindNumbersForASlot(grid,ii,jj,divisions);
            if (~isempty(elementsAt(ii,jj).elems) && length(elementsAt(ii,jj).elems) < candidates)
                candidates = length(elementsAt(ii,jj).elems);
                i_min = ii;
                j_min = jj;
            end
        end
    end
end
end