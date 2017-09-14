% The VLFeat toolbox 
% gives a undefined error if we
% encapsulate it all in a function.
% Don't know exactly how to make it work properly.

close all;
im = imread('texturesimages\forest\forest_7.jpg');
im = single(rgb2gray(im));
F = vl_lbp(im, 100);

list = zeros (1, size(F,3));

for i=1 : size(F,3);
    list(1,i) = F(:,:,i);
end

media = mean(list);