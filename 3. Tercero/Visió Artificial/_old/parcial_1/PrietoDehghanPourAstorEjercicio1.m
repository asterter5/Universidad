function [ ] = PrietoDehghanPourAstorGrupF( )
% FUNCTION PrietoDehghanPourAstorGrupF
%   Function behaves as described in 'Examen practico 2'
    close all;
    file1 = 'images_group2/monkey1.png';
    file2 = 'images_group2/monkey2.png';
    monkey1 = rgb2gray(imread(file1));
    monkey2 = rgb2gray(imread(file2));
    
    sigma_low = 2;
    sigma_high = 4;
    monkey1_filter = fspecial('Gaussian', 4*sigma_low+1, sigma_low);
    monkey2_filter = fspecial('Gaussian', 4*sigma_high+1, sigma_high);

    hybrid_monkey = imfilter(monkey2, monkey2_filter) + (monkey1 - imfilter(monkey1, monkey1_filter));
    
    scales = 6; %how many downsampled versions to create
    scale_factor = 0.5; %how much to downsample each time
    padding = 1; %how many pixels to pad.
    original_height = size(hybrid_monkey, 1);
    output = hybrid_monkey;
    cur_image = hybrid_monkey;
    for i = 2:scales
        %add padding
        output = cat(2, output, ones(original_height, padding));
        %dowsample image;
        cur_image = imresize(cur_image, scale_factor, 'bilinear');
        %pad the top and append to the output
        tmp = cat(1,ones(original_height - size(cur_image,1), size(cur_image,2)), cur_image);
        output = cat(2, output, tmp);    
    end
    
    figure, subplot(2, 3, 1), imshow(monkey1), title('Monkey 1'),...
        subplot(2, 3, 2), imshow(monkey2), title('Monkey 2'),...
        subplot(2, 3, 3), imshow(hybrid_monkey), title('Hybrid Monkey'),...
        subplot(2, 3, 5), imshow(output), title('Downscaled Image');
end

