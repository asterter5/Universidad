image_model = imread('images_p1\model.png');        %reading the two image files.
image_coat = imread('images_p1\coat.png');
imfinfo('images_p1\model.png')
imfinfo('images_p1\coat.png')

image_coat_gray = rgb2gray(image_coat);             %converting the coat to grayscale.
imwrite(image_coat_gray, 'images_p1\coat_gray.png');

s_coat = size(image_coat);                          %doing the binary conversion of the grayscale coat.
image_coat_binary = zeros(s_coat(1), s_coat(2), 'logical');
th_umbrale = 130; %Umbrale to be changed if is needed to do a better binary translation

for k = 1:s_coat(1)
    for j = 1:s_coat(2)
        if image_coat(k, j) >= th_umbrale
           image_coat_binary(k, j) = 1;
        end
    end
end

imwrite(image_coat_binary, 'images_p1\coat_binary1.png');       %saving the binary conversions of the coat.
imwrite(~image_coat_binary, 'images_p1\coat_binary2.png');

image_coat = imfuse(image_coat, image_coat_binary);             %fusing the resulting binary coat with the model.
image_result = imadd(image_model, image_coat);
imwrite(image_result, 'images_p1\model_coat.png');              %saving the final image to storage.

figure, subplot(1, 3, 2), imshow(image_result)
