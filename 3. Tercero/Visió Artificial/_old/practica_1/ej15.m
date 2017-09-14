function [ ] = ej15(file)
%EJ15 This function reads a given file and separates its RGB channels.

image6 = imread(file);
imfinfo(file)

s = size(image6);
imR = image6(:,:,1); %RED
imG = image6(:,:,2); %GREEN
imB = image6(:,:,3); %BLUE

image61 = zeros(s(1), s(2), 'uint8'); %creating a new matrix that will have the original RGB channels switched.
image61(:,:,1) = imB;
image61(:,:,2) = imG;
image61(:,:,3) = imR;

% imG = imG * 0; -> This turns the Channel to black.

figure, subplot(2, 3, 2), imshow(image6)    %showing the different versions of the image.
    subplot(2, 3, 3), imshow(image61)
    subplot(2, 3, 4), imshow(imR)
    subplot(2, 3, 5), imshow(imG)
    subplot(2, 3, 6), imshow(imB)

imwrite(image61, 'images_p1\3channels.jpg');    %saving the results to storage
end
