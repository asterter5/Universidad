close all;
file = 'material_P3/loro.png';
image = imread(file);

% Grayscale Processing of the image
k_1 = 5; % Value k
im_gray = rgb2gray(image); % GrayScale parrot

% Creating 2D Chars from 1D.
X_1 = double(reshape(im_gray, [size(image, 1) * size(image, 2), 1]));
X_1 = [X_1 X_1];
[idx1, C1] = kmeans(X_1, k_1);

pixel_labels = reshape(idx1, [size(im_gray, 1), size(im_gray, 2)]);
figure, 
subplot(1,2,1), imshow(im_gray),
subplot(1,2,2), imshow(pixel_labels, []);

% RGB Colour Processing of the image
k_2 = 16; % Value k

X_2 = double(reshape(image, [size(image, 1) * size(image, 2), size(image, 3)]));
[idx2, C2] = kmeans(X_2, k_2); % Apply kmeans
pixel_labels = reshape(idx2, [size(image, 1), size(image, 2)]);

color = int16(C2);
imcluster = zeros(size(image, 1), size(image, 2), 3);

% Channels to save the translated colours from 'int16'
image_R = zeros(size(image, 1), size(image, 2)); 
image_G = zeros(size(image, 1), size(image, 2));
image_B = zeros(size(image, 1), size(image, 2));

for i=1:k_2
    image_R(pixel_labels==i) = color(i,1);
    image_G(pixel_labels==i) = color(i,2);
    image_B(pixel_labels==i) = color(i,3);
end

% Adding Channels to the simplified colour image
imcluster(:,:,1) = image_R;
imcluster(:,:,2) = image_G;
imcluster(:,:,3) = image_B;
imcluster = uint8(imcluster);

% display the final processed images
figure, 
subplot(2,2,1), imshow(image), subplot(2,2,2), plotPixelDistribution(image),
subplot(2,2,3), imshow(imcluster), subplot(2,2,4), plotPixelDistribution(imcluster);