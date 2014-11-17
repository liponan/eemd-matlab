function [modes, O, P, Q] = eemd3(img, goal, ens, nos_wn)
% this code is the interface function of the 3D EEMD.
% mex and parfor supported.
% written by Neil Po-Nan Li @ Inst. of Physics, Academia Sinica, Taiwan
% v1. 2014/03/17


%%

sz = size(img);
n1 = sz(1);
n2 = sz(2);
n3 = sz(3);

std_img = std( img(:) );
img = img ./ std_img; % normalize data

%% 3-D EEMD    dim#1

data = img;
O = zeros(n1, n2, n3, goal+1);

disp('========== dimension #1 ==========');

tic;
% time_pre = 0;
% count = 0;
parfor w = 1:n3
    disp(['Solving layer ' num2str(w) '/' num2str(n3) ]);
    for u = 1:n1
        % solve and store
        row_modes = eemd( data(u,:,w), goal, ens, nos_wn);
        row_modes( isnan(row_modes) ) = 0;
        O(u,:,w,:) = permute(row_modes, [4 2 3 1]);
    end
end
toc

%% 3-D EEMD    dim#2

P = zeros(n1, n2, n3, goal+1, goal+1);

disp('========== dimenstion #2 ==========');

tic;% time_pre = toc;
for m = 1:(goal+1)
    disp(['Solving mode ' num2str(m) '/' num2str(goal+1) ]);
    parfor w = 1:n3
        for v = 1:n2
            % solve and store
            col_modes = eemd( O(:,v,w,m).', goal, ens, nos_wn);
            col_modes( isnan(col_modes) ) = 0;
            P(:,v,w,m,:) = permute(col_modes, [2 5 4 3 1]);
        end
    end
end
toc
clear O;

%% 3-D EEMD    dim#3

Q = zeros(n1, n2, n3, goal+1, goal+1, goal+1);

disp('========== dimenstion #3 ==========');

tic;% time_pre = toc;
for m1 = 1:(goal+1)
    Qtmp = zeros(n1, n2, n3, goal+1, goal+1);
    Ptmp  = P(:,:,:,:,m1);
    for m2 = 1:(goal+1)
        disp(['Solving mode ' num2str(m2) '/' num2str(goal+1)...
            ' in mode ' num2str(m1) '/' num2str(goal+1)]);   
        parfor v = 1:n2
            for u = 1:n1
                % solve and store
                stk = permute( Ptmp(u,v,:,m2), [1 3 2 4]);
                stk_modes = eemd(stk, goal, ens, nos_wn);
                stk_modes( isnan(stk_modes) ) = 0;
                Qtmp(u,v,:,m2,:) = permute(stk_modes, [5 4 2 3 1]);
            end
        end    
    end
    
    Q(:,:,:,:,m1,:) = permute( Qtmp, [1 2 3 4 6 5]);

end
toc
clear P;


%% Combine modes



R = zeros(n1, n2, n3, goal+1);

for m = (goal+1):-1:1
    R(:,:,:,m) = sum( sum( sum( Q(:,:,:,m:end,m:end,m:end), 4), 5), 6);
    if m < (goal+1)
        R(:,:,:,m) = R(:,:,:,m) - sum( R(:,:,:,(m+1):end), 4);
    end 
end
clear Q;

modes = R .* std_img; % unnormalize data

