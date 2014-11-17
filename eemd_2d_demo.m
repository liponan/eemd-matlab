% clc;
% clear all;
close all;

%% parameters

nos_img = 0.1;
goal = 3;
ens = 100;
nos_wn = 0.1;

%% load data


load lena64;
img = lena;

std_img = std( img(:) );
sz = size(img);
img2 = (img./std_img + randn(sz).*nos_img ).*std_img;

figure;
subplot(1,2,1);
imagesc(img);
colormap(bone);
axis off;
axis image;
title('original data');
subplot(1,2,2);
imagesc(img2);
colormap(bone);
axis off;
axis image;
title(['\sigma = ' num2str(nos_img) ' noise added']);

%% 2-D EEMD  

tic;
[H, G, D] = eemd2(img2, goal, ens, nos_wn);
toc

%% show result
for k = 1:goal
    figure;
    imagesc(H(:,:,k));
    colormap(bone);
    axis off;
    axis image;
    title(['mode #' num2str(k)]);
end
figure;
imagesc(H(:,:,goal+1));
colormap(bone);
axis off;
axis image;
title('trend');


figure;
subplot(1,2,1)
imagesc(img);
colormap(bone);
axis off;
axis image;
title('original');
subplot(1,2,2)
imagesc( sum(H, 3) );
colormap(bone);
axis off;
axis image;
title('reconstructed');
