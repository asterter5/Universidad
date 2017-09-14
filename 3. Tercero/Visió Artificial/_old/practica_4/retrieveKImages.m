function [] = retrieveKImages()

    files = dir(fullfile('images', '*.jpg'));
    x = size(files, 1);
        
    allFeatures = getClassFeatures('images'); %Retrieving features of all images.

    % For every image
    for a=1:x
        image = imread(fullfile('images', files(a).name)); % Image query
        
        im = allFeatures(a, :); % Image query descriptor
        
        % Delete self feature vector, so image doesn't compare to itself.
        features = deleteDescriptor(allFeatures, im);
        
        % Searches the 9 most similar images with knnsearch of K = 9
        [idx, d] = knnsearch(features, im, 'K', 10);
            
        key = d;
        value = idx;
        
        % Sorts similarities in descending order
        similarImages = sort(containers.Map(key,value),'descend');
        
        % Shows the query image and the 9 most similiar images found among all the images
        figure, subplot(2,5,1),imshow(image), title('Query image');
        for k=1:9
            subplot(2,5,k+1);
            imshow(imread(fullfile('images', files(similarImages(d(k))).name))), title('Retrieved image by similarity');     
        end   
    end
end

function [features] = deleteDescriptor(features, im)
    % This function searches for the texture descriptor passed as parameter
    % in the matrix of all the features and sets it to a vector of  zeros
    % so the knnsearch method doesn't take the image itself in
    % consideration when finding the K most similar images.
    for k=1:size(features,1)
        if(features(k,:)== im) 
                features(k,:)=zeros();
            break
        end
    end   
end