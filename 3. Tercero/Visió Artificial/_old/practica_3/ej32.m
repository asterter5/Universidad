close all;

% Generating point cloud with gaussRandom
std = 0.1; % standard deviation
nump = 100;  % number of points

C_1 = gaussRandom([1 2], std, nump); % Cloud1: center 1 2
C_2 = gaussRandom([2 2], std, nump); % Cloud2: center 2 2
C_3 = gaussRandom([2 1], std, nump); % Cloud3: center 2 1
C = [C_1; C_2; C_3];

% Displaying each points cloud with different colors.
figure, hold on, 
plot(C_1(:,1), C_1(:,2), '.'), 
plot(C_2(:,1), C_2(:,2), '.'), 
plot(C_3(:,1), C_3(:,2), '.'),
hold off,
title 'Three point clouds [gaussRandom]';

% K-Means Clustering of the data
k = [2 3 4]; % number of centers
n = size(k,2); % number of clusters

figure, subplot(2,3,2), % Display of the original data
scatter(C_1(:,1), C_1(:,2), 'filled'), hold on,
scatter(C_2(:,1), C_2(:,2), 'filled'), hold on,
scatter(C_3(:,1), C_3(:,2), 'filled'), hold off,
title 'Original data';

for i=1:n % iterating through the different 'k'
    [idx, CF] = kmeans(C,k(i));
    labels = []; % Labels for the legend to plot
    
    % Display of clustered data
    subplot(2,n,n+i),
    for j=1:k(i) % iterating through clusters formed by using kmeans   
        labels = vertcat(labels, ['Cluster ', int2str(j)]); % Create legend labels
        scatter(C(idx==j,1),C(idx==j,2), 'filled'), hold on,     
    end
    
    plot(CF(:,1),CF(:,2),'ko','MarkerSize',12,'LineWidth',2), % plotting cluster centers
    title (strjoin({'k=', int2str(k(i))})),
    legend({vertcat(labels, 'Centroids')},'FontSize',6, 'Location','NW'),
end
