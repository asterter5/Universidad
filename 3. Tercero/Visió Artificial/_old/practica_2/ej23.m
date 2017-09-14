close all;
file='images_p2/logo.png';
im=imread(file);

imGray=rgb2gray(im);

sobel_im = edge(imGray, 'Sobel'); %Sobel method
prewitt_im = edge(imGray, 'Prewitt'); %Prewitt method
log_im = edge(imGray, 'log'); %Laplacian of Gaussian method
canny_im = edge(imGray, 'Canny'); %Canny edges method (Best Naive Aproximation)

figure, subplot(2,4,2), imshow(im, []), title('Original image'),...
subplot(2,4,3),imshow(sobel_im), title('Sobel image'),...
subplot(2,4,4),imshow(prewitt_im), title('Prewitt image'),...
subplot(2,4,5),imshow(log_im), title('Laplacian of Gaussian image'),...
subplot(2,4,6),imshow(canny_im), title('Canny edges image');