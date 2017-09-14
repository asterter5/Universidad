function [] = visualizeFeatures()
    % Shows the features 25 and 41 of each class of images in directory. 
    
    % Getting the features matrix of the tree images DB.
    b_features = getClassFeatures('texturesimages/buildings');
    f_features = getClassFeatures('texturesimages/forest');
    s_features = getClassFeatures('texturesimages/sunset');
    
    figure,
    hold on;
    % Plotting the 'building' features (25, 41) with red '+'.
    plot(1:size(b_features,1),b_features(:,25),'r+',1:size(b_features,1),b_features(:,41),'r+');
    % Plotting the 'forest' features (25, 41) with green 'x'.
    plot(1:size(f_features,1),f_features(:,25),'gx',1:size(f_features,1),f_features(:,41),'gx');
    % Plotting the 'sunset' features (25, 41) with blue 'o'.
    plot(1:size(s_features,1),s_features(:,25),'bo',1:size(s_features,1),s_features(:,41),'bo');
    hold off;

end

