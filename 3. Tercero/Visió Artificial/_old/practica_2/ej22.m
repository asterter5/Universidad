close all;
file='images_p2/doulphin.jpg';
file2='images_p2/face.png';
im=imread(file);
im2=imread(file2);

%imGray=rgb2gray(im);

h_hor = fspecial('gaussian', 15, 2); %the second parameter (hsize) defines the len of the row of the mask, and the third one (sigma),
                                     %the standard deviation the Gaussian mask will apply (BETTER THE CLOSER TO 1).
h_hor2 = fspecial('average', 25);


smoothedIm2D_hor = imfilter(double(im), h_hor);
smoothedIm2D_hor2 = imfilter(double(im2), h_hor2);

for j=1:100
    smoothedIm2D_hor1 = imfilter(double(im), h_hor);
end

im2 = double(im2) - smoothedIm2D_hor2;

figure, subplot(3,4,2),imshow(im, []), title('Original image'),...
subplot(3,4,5),imshow(im), title('Gray image'),...
subplot(3,4,6),imshow(uint8(smoothedIm2D_hor)),title('Smoothed image (2D)'),...
subplot(3,4,7),imshow(uint8(smoothedIm2D_hor1)),title('Smoothed image 100 (2D)'),...
subplot(3,4,8),imshow(uint8(smoothedIm2D_hor2)),title('Smoothed image A (2D)'),...
subplot(3,4,4),imshow(im2), title('im2 - smIm2D_hor2');