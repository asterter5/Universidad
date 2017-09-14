function [matrix] = getClassFeatures(directory) 
    matrix = zeros(30, 48);
    % Reading all the files in the directory.
    files = dir(fullfile(directory, '*.jpg'));
    
    for i=1:size(files, 1);
        % Getting the features of each file.
        file = fullfile(directory, files(i).name);
        features = getFeatures(file); % extract image features row.
        matrix(i, :) = features;      % insert into matrix.
    end
    close all;
end