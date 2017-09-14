close all;
model_file = 'material_P3/starbucks.jpg'; % Base image (Model)

% List of Starbucks images
list_images = ['material_P3/starbucks2.png';'material_P3/starbucks4.jpg';'material_P3/starbucks5.png';'material_P3/starbucks6.jpg';'material_P3/starbucks7.jpg'];
celldata = cellstr(list_images);

match_values = zeros(1,6);
for i=1:5
   % get the matches for the model
   match = size(showMatches(model_file,celldata{i}));
   % save in list
   match_values(i) = match(2);
end

figure,
    subplot(3,3,2),imshow(model_file),title('Model');
for i=1:5
    % get the max matching value in list 
    pos=find(match_values==max(match_values));
    % show image in a figure
    subplot(3,3,i+3),imshow(celldata{pos}),title(i);
    % Reset the max matching value
    match_values(match_values==max(match_values))=0;
end

