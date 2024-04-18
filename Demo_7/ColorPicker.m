%%%%%%%%%%%%%%%%%%%%%
% Christopher Wall
% u1467634
% ME EN 1010 Lab Section 15
% HW10
% Due DATE 2/12/2024
%%%%%%%%%%%%%%%%%%%%%
function [ RGBvals ] = ColorPicker(imgArray)
    image(imgArray);
    [xCoord, yCoord] = ginput(1);
    xCoord = round(xCoord);
    yCoord = round(yCoord);
    RGBvals =  imgArray(yCoord , xCoord, 1:3 );
    close;
end
% Christopher Wall
% u1467634