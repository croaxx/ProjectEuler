function y=ReadGridsFromFile(path,numSlotElements)

fid = fopen(path);
fgetl(fid);
tline = fgetl(fid);
counter = 1;
row_ = 1;
it = 0;
while ischar(tline)
    if (mod(counter,10) ~= 0)
        for ii=1:length(tline)
            grids_(row_,ii+it) = str2num(tline(ii));
        end
        it = it + numSlotElements;
    else
        row_ = row_ + 1;
        it = 0;
    end
    counter = counter + 1;
    tline = fgetl(fid);
end
fclose(fid);

y = grids_;
end