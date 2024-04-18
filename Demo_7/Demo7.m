% Christopher Wall u1467634
% Lab section 15
clear, clc, close all

%% 
imageFileName = 'S24_Demo4_A1.bmp';
targetImage = imread(imageFileName);
disp("Click on the snout of the whacked mole to get color information");
keyRBG = ColorPicker(targetImage);
targetRBG = keyRBG - 1;
[centroidRows, centroidCols, modImage] = FindAllTargetCentroids(targetImage, targetRBG);
figure;
image(modImage);
hold on;
plot(centroidCols, centroidRows, 'wx');

stripeNum = centroidRows./10;
xTarget = (450 + centroidCols)./1000;

combinedMatrix = [stripeNum(:), xTarget(:)];

sortedMatrix = sortrows(combinedMatrix, 'descend');

stripeNum = sortedMatrix(:, 1);
xTarget = sortedMatrix(:, 2);

tempStripe = stripeNum(end-1);
tempTarget = xTarget(end-1);

%swap the second to last distance and the first distance since the launcher
%is already close to home for the first shot
stripeNum(5) = stripeNum(1);
stripeNum(1) = tempStripe;
xTarget(5) = xTarget(1);
xTarget(1) = tempTarget;

%%

% serial communication setup
% /dev/tty.usbmodem1101 is used since this is being run from a mac (same
% port as shown in arduino environment)
RomeoCOM = serialport('/dev/cu.usbmodem1101',9600);
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
kbhit('init');
key = char(0);
prevKey = key;

while(1)
    % key press detection
    prevKey = key;
    key = kbhit;
    pause(1/6000)
    if  key == 'q'
        disp('MATLAB aborting')
        break
    elseif key ~= char(0)
        disp('sending letter to Arduino')
        writeline(RomeoCOM,key)
    end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0   
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        
        % if romeo sends special done message, break out of scanning loop
        if strcmp(message, endCheck) == 1
            break
        elseif strcmp(message, dataCheck) ==1 
            % send and recieve messages back
            disp('sending data to Romeo')
            for target = 1:6
                % send mssg as string to romeo
                out1 = sprintf('%d', stripeNum(target) );
                writeline(RomeoCOM, out1);
                out2 = sprintf('%.3f', xTarget(target));
                writeline(RomeoCOM, out2);
                message = readline(RomeoCOM);
                message = erase(message, sprintf('\r'));
                disp(message);
            end
        else
            disp(message)
        end
    end
end

clear RomeoCOM
kbhit('stop');