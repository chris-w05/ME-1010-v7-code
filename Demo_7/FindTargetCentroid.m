function [centroidRow, centroidCol, modImage] = FindTargetCentroid(inImage, targetRGB)
% 2. Index color layers
redLayer = inImage(:,:,1);
greenLayer = inImage(:,:,2);
blueLayer = inImage(:,:,3);

% 4. Logical array for red/target pixels
logArray = redLayer == targetRGB(1) & greenLayer == targetRGB(2) & blueLayer == targetRGB(3);

% 5. Find matching coordinates
[matchRows, matchCols] = find(logArray);

% 6. Index coordinates of top left corner
firstMatchRow = matchRows(1);
firstMatchCol = matchCols(1);

% 7. Determine image size
[rows, cols, ~] = size(inImage);

% 8. Loop to find last match column
for col = firstMatchCol:cols
    if logArray(firstMatchRow, col+1) == 0
        break;
    end
end
lastMatchCol = col;

% 9. Loop to find last match row
for row = firstMatchRow:rows
    if logArray(row+1, firstMatchCol) == 0
        break;
    end
end
lastMatchRow = row;

% 10. Compute centroid
centroidRow = ((firstMatchRow + lastMatchRow) / 2);
centroidCol = ((firstMatchCol + lastMatchCol) / 2);

% 11. Make copy of testImage
modImage = inImage;

% 12. Change red/target pixels to black
modImage(firstMatchRow:lastMatchRow, firstMatchCol:lastMatchCol, :) = 0;
end