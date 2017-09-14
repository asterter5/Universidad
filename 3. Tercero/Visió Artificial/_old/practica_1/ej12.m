image3 = imread('images_p1\car_lowContrast.jpg'); %reading the image file.
imfinfo('images_p1\car_lowContrast.jpg')

image31 = image3 + min(min(image3));              %saving the lowContrast and highContrast versions of the matrix.
image32 = image3 - min(min(image3));
image33 = imadjust(double(image3)/255);

imhist(image3)                                    %showing the original image histogram.
imwrite(image31, 'images_p1\car_bright.jpg');     %saving the 3 versions of the original image
imwrite(image32, 'images_p1\car_dark.jpg');
imwrite(image33, 'images_p1\car_contrast.jpg');

figure, imshow(image3)
figure, imshow(image31)
figure, imshow(image32)
figure, imshow(image33)
