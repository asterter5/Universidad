close all;
file = 'material_P3/Barcelona.mp4';
vid = VideoReader('material_P3/Barcelona.mp4');

fr_1 = readFrame(vid);

k = 1;
j = 1;
figure, 
while hasFrame(vid) % while there are still frames in the video
    matrix(:,:,:,j) = fr_1; % saving the actual frame into the matrix
    fr_2 = readFrame(vid);

    % Saving the histograms of the frames to compare
    fr_R1 = imhist(fr_1(:,:,1));
    fr_G1 = imhist(fr_1(:,:,2));
    fr_B1 = imhist(fr_1(:,:,3));

    fr_R2 = imhist(fr_2(:,:,1));
    fr_G2 = imhist(fr_2(:,:,2));
    fr_B2 = imhist(fr_2(:,:,3));

    % Histogram vector sum for the used frames
    h_F1 = fr_R1 + fr_G1 + fr_B1;
    h_F2 = fr_R2 + fr_G2 + fr_B2;

    % Eucleidan distance between the histogram vectors sum. 2 dimensions
    distances(k) = norm(h_F1 - h_F2, 2);

    % if dist is higher than the optimal value of '40000'
    if distances(k) > 40000
        % median value of the shot (static image)
        imshow(median(matrix,4));
        
        clear m;
        pause(0.01);

        j = 1;
    end

    k = k + 1;
    j = j + 1;
    fr_1 = fr_2;
end