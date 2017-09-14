function [ ] = PrietoDehghanPourAstorGrupF( )
% FUNCTION PrietoDehghanPourAstorGrupF
%   Function behaves as described in 'Examen practico 2'
    close all;
    file = 'images_group2/tetris.png';
    image = imread(file);
    
    image2 = image;
    image3 = rgb2gray(image);

    color_green = [34 177 77]';
    color_orange = [255 127 38]';

    for i = 1:size(image, 1)
        for j = 1:size(image, 2)
            color = squeeze(image(i, j, :));
            if isequal(color, color_green)
                image2(i, j, :) = color_orange;
            elseif isequal(color, color_orange)
                image2(i, j, :) = color_green;
            end
        end
    end
    
    image4 = zeros(size(image3, 1), size(image3, 2), 'logical');
    th_umbrale = 100;
    
    for k = 1:size(image3,1)
        for j = 1:size(image3,2)
            if (image3(k, j) <= th_umbrale) && (image3(k, j) ~= 0) % Should check if value is below threshold and if value is not foreground ('0' value)
                image4(k, j) = 1;
            end
        end
    end
    
    % imtool(image3)
    figure, subplot(2, 3, 1), imshow(image), title('Original'),...
        subplot(2, 3, 2), imshow(image2), title('Enhanced'),...
        subplot(2, 3, 3), imshow(image3), title('Grayscale'),...
        subplot(2, 3, 5), imshow(image4), title('Binary');
end

