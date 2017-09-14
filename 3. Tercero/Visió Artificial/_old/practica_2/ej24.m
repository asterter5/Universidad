close all;
file='images_p2/einstein.jpg';
file2='images_p2/monroe.jpg';
einstein_im = imread(file);
monroe_im = imread(file2);

sigma_low = 4;
sigma_high = 6;
einstein_filter = fspecial('Gaussian', 4*sigma_low+1, sigma_low);
monroe_filter = fspecial('Gaussian', 4*sigma_high+1, sigma_high);

%Einstein image is Low-Pass and Monroe image is High-Pass
hybrid_im = imfilter(monroe_im, monroe_filter) + (einstein_im - imfilter(einstein_im, einstein_filter));
%hybrid_im = imfilter(einstein_im, einstein_filter) + (monroe_im - imfilter(monroe_im, monroe_filter));

scales = 5; %how many downsampled versions to create
scale_factor = 0.5; %how much to downsample each time
padding = 5; %how many pixels to pad.

original_height = size(hybrid_im, 1);
num_colors = size(hybrid_im, 3); %counting how many color channels the input has
output = hybrid_im;
cur_image = hybrid_im;

for i = 2:scales
    %add padding
    output = cat(2, output, ones(original_height, padding, num_colors));
    
    %dowsample image;
    cur_image = imresize(cur_image, scale_factor, 'bilinear');
    %pad the top and append to the output
    tmp = cat(1,ones(original_height - size(cur_image,1), size(cur_image,2), num_colors), cur_image);
    output = cat(2, output, tmp);    
end

figure, subplot(2,4,2), imshow(einstein_im), title('Einstein image'),...
subplot(2,4,3),imshow(monroe_im), title('Monroe image'),...
subplot(2,4,5),imshow(hybrid_im), title('Hybrid image'),...
subplot(2,4,7),imshow(output), title('Downscaled hybrid images');
