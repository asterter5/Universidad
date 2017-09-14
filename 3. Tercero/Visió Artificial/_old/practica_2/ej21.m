function [] = ej21() % file is the name of the image
%ej21 This function illustrates the effect of resizing and smoothing with different 1D and 2D masks

close all;
file='images_p2/face.png';
file2='images_p2/doulphin.jpg';

im=imread(file2);

imGray=rgb2gray(im);
resizedIm=imresize(imGray, 2);

h_hor=[1 1 1 1 1]; % 1D mask defined
h_hor=h_hor/sum(h_hor); % normalizations
    
% define a vertical mask and apply it on the gray image.
for k=1:1000
    smoothedImGray1D_hor=imfilter(double(imGray),h_hor);
end
% Repeat the smoothing several times in order to remove the line in the middle.

% Look for alternative of the mean filter to remove the line in the middle.
%smoothedImGray1D_...=

% define the 2D mask, shell we normalize it?
h_hor2 = [[1 1 1 1 1],[1 1 1 1 1],[1 1 1 1 1]]; %the DIM of the filter matrix determines the DIM of the mask.
h_hor2 = h_hor2/sum(h_hor2);                    %the len of each row of the filter matrix determines how much neighbors pixels we look at.

for j=1:1000
    smoothedImGray2D_hor = imfilter(double(imGray), h_hor2); %convolving with a 2D mask
end                                                          %if we do not normalize the mask, it will fuck up the image's histogram.

figure, subplot(3,4,2),imshow(im, []), title('Original image'),...
subplot(3,4,5),imshow(imGray), title('Gray image'),...
subplot(3,4,6),imshow(resizedIm),title('Resized image'),...
subplot(3,4,7),imshow(uint8(smoothedImGray1D_hor)),title('Smoothed image (1D)'),...
subplot(3,4,8),imshow(uint8(smoothedImGray2D_hor)),title('Smoothed image (2D)'),...
subplot(3,4,9),imhist(imGray), title('Histogram of Original im.'), ... %THE HISTS ARE DONE CHANNEL BY CHANNEL, NOT IN RGB(COLOURED) CHANNELS
subplot(3,4,10),imhist(resizedIm),title('Histogram of resized im.'),...
subplot(3,4,11),imhist(uint8(smoothedImGray1D_hor)),title('Histogram of smoothed image (1D)'),...
subplot(3,4,12),imhist(uint8(smoothedImGray2D_hor)),title('Histogram of smoothed image (2D)');