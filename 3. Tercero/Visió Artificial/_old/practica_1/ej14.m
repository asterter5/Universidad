image5 = rgb2gray(imread('images_p1\circles.bmp')); %reading the image file and converting it to grayscale
imfinfo('images_p1\circles.bmp')

figure, imshow(image5)

s = size(image5);                       %setting up the different binary matrixes that will save the three circles.
image51 = zeros(s(1), s(2), 'logical');
image52 = zeros(s(1), s(2), 'logical');
image53 = zeros(s(1), s(2), 'logical');
for k = 1:s(1)                          %saving each circle in a separate binary matrix
    for j = 1:s(2)
        if image5(k, j) == 0
            image51(k, j) = 1;
        elseif image5(k, j) == 127
            image52(k, j) = 1;
        elseif image5(k, j) == 195
            image53(k, j) = 1;
        end
    end
end

figure, imshow(image51)                 %showing the resulting images.
figure, imshow(image52)
figure, imshow(image53)

i51 = zeros(s(1), s(2), 'uint8');       %setting up the last 3 matrixes that will hold the separate original circles.
i52 = zeros(s(1), s(2), 'uint8');
i53 = zeros(s(1), s(2), 'uint8');
for k = 1:s(1)                          %the binary images are converted into their original values in separate images.
    for j = 1:s(2)
        if image51(k, j) == 1
            i51(k, j) = image5(k, j);
            i52(k, j) = 255;
            i53(k, j) = 255;
        elseif image52(k, j) == 1
            i51(k, j) = 255;
            i52(k, j) = image5(k, j);
            i53(k, j) = 255;
        elseif image53(k, j) == 1
            i51(k, j) = 255;
            i52(k, j) = 255;
            i53(k, j) = image5(k, j);
        else
            i51(k, j) = 255;
            i52(k, j) = 255;
            i53(k, j) = 255;
        end
    end
end

figure, imshow(i51)                    %showing the results.
figure, imshow(i52)
figure, imshow(i53)
