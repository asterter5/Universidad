close all;
file = 'images_p2/BigBang.mp4';
vid = VideoReader(file);

vid_H = vid.Height;
vid_W = vid.Width;

frames = struct('cdata', zeros(vid_H, vid_W, 3, 'uint8'),...
    'colormap', []);

h_hor = [[1 1 1 1 1], [1 1 1 1 1]] / 10; %convolving with a 2D mask

k = 1;
while hasFrame(vid)
    frames(k).cdata = imfilter(readFrame(vid), h_hor);
    k = k + 1;
end

implay(frames);
