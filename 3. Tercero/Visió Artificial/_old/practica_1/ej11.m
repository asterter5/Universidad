image1 = imread('images_p1\lena.jpg');  %reading the image file.
imfinfo('images_p1\lena.jpg')

image2 = rgb2gray(image1);              %turning the image to grayscale.
imgSize = size(image2);

frame = zeros(uint8(imgSize(1) + imgSize(1)/10), uint8(imgSize(2) + imgSize(2)/10),'uint8');

for k = 23:225                          %creating the frame that will surround the image matrix.
    for j = 23:225
        frame(k, j) = image2(k, j);
    end
end

imwrite(frame, 'images_p1\lena_frame.jpg'); %saving to storage and showing the results.
figure, imshow(frame)
