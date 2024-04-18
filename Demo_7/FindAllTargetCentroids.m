function [rowCoords, colCoords, modImage] = FindAllTargetCentroids(imageArray, targetRGB);
    for( targetNum = 1:6)
        [rowCoords(targetNum), colCoords(targetNum), imageArray] = FindTargetCentroid(imageArray, targetRGB);
    end
    modImage = imageArray;
end