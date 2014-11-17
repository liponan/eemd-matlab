% this code is for testingthe 3D EEMD
% run 'matlabpool open 8' before running this code to enable parallel comp.
% written by Neil Po-Nan Li @ Inst. of Physics, Academia Sinica, Taiwan
% v1. 2014/03/17

load mimivirus_B;
img = B;

goal = 1;
ens = 100;
nos_wn = 1;

%% run eemd3

R = eemd3(img, goal, ens, nos_wn);


%% show modes

close all;
load dkbluered;

for m = (goal+1):-1:1
    figure(m),
    imagesc( sum(R(:,:,:,m), 3) );
    axis image;
    colorbar;
    if m == (goal+1)
        title('xy proj. of trend');
        colormap(jet);
    else
        title(['xy proj. of mode #' int2str(m)]);
        colormap(dkbluered);
        caxis([-max(max(abs(sum(R(:,:,:,m), 3)))) max(max(abs(sum(R(:,:,:,m), 3))))]);
    end
end

