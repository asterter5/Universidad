close all;
numLevels = 3;    % Defining the number of levels for the classifier.
numFeatures = 2;  % Defining the number of weak-detectors per level.

% Starting level, creates all the needed variables for the next levels.
[outClass, X, Y, selFeatures, error, predErr] = haarFeatureDemo(numFeatures);
finalError = [];
finalError = [finalError error(1)]; %Create the finalError variable, and add the current error to it.

for i=2:numLevels % For each level needed:
    [outClass, newX, newY, selFeatures, error, predErr] = haarFeatureDemo(numFeatures, X, Y, outClass);
    finalError = [finalError error(1)]; % The new error is added to the vector.
end

close all; % Showing the error-per-level plotted.
figure, plot(finalError), title('Prediction error');
