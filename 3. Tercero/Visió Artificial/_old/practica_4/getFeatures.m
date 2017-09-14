function [descriptor] = getFeatures(file)
    image = imread(file);
    image_gray = rgb2gray(image);
    
    F = makeLMfilters(); % return filters
    
    % Calculate the descriptor applying the mean of convolution
    figure,
    descriptor = zeros(1, size(F,3));
    for i = 1:size(F,3);
       res = conv2(double(image_gray), F(:,:,i), 'valid');
       % Calculate the descriptor applying the mean of convolution
       descriptor(1,i) = mean(mean(res));
       subplot(9,6,i), imagesc(res); colorbar;
    end
end