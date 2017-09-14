image7 = imread('images_p1\logo.png');          %reading the image file.
imfinfo('images_p1\logo.png')

imR = image7(:,:,1);                            %separating its RGB channels.
imG = image7(:,:,2);
imB = image7(:,:,3);

vR = find(imR == 6);                            %getting specific values vector from the colour channels.
vG = find(imG == 118);
vB = find(imB == 85);

sR = size(vR);
for k = 1:sR                                    %saturating the R channel to turn the logo from green to red.
    imR(vR(k)) = 255;
end
sG = size(vG);
for k = 1:sG                                    %eliminating the other 2 colour channels.
    imG(vG(k)) = 0;
end
sB = size(vB);
for k = 1:sB
    imB(vB(k)) = 0;
end

s = size(image7);
image71 = zeros(s(1), s(2), 'uint8');       %setting up a new matrix that will save the new image.
image71(:,:,1) = imR;
image71(:,:,2) = imG;
image71(:,:,3) = imB;

figure, subplot(1, 3, 2), imshow(image7)
    subplot(1, 3, 3), imshow(image71)

imwrite(image71, 'images_p1\logo_red.png'); 
