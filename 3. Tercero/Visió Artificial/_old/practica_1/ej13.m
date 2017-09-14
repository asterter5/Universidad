image4 = imread('images_p1\car_gray.jpg');  %reading the image file
imfinfo('images_p1\car_gray.jpg')

s = size(image4);                           %setting up the values that will conform the binary matrix. (th_umbrale)
image41 = zeros(s(1), s(2), 'logical');
th_umbrale = 130;                           %umbrale to be changed if is needed to do a better binary translation

for k = 1:s(1)                              %translating the original image into a binary one based on the threshold given.
    for j = 1:s(2)
        if image4(k, j) >= th_umbrale
           image41(k, j) = 1;
        end
    end
end

imwrite(image41, 'images_p1\car_binary.jpg'); %saving to storage ans showing the image.
figure, imshow(image41)
