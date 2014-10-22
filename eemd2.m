function [modes, G, D] = eemd2(img, goal, ens, nos_wn)
% 2-D EEMD, an implenmation of HHT
% written by Neil Po-Nan Li @ Inst. of Physics, Academia Sinica, Taiwan
% v1.  2012/10/6
% v2.  2014/3/10 bug fixes
% v2.1 2014/3/17 stablity issue fixed

sz = size(img);
n1 = sz(1);
n2 = sz(2);


std_img = std( img(:) );
img = img ./ std_img;

%% 2-D EEMD    dim#1

data = img;
G = zeros(sz(1), sz(2), goal+1);
tic;
% time_pre = 0;
% count = 0;
parfor u = 1:n1
%     disp(['Solving row ' num2str(u) '/' num2str(n1) ]);
    
    % solve and store
    row_modes = eemd(data(u,:), goal, ens, nos_wn);
    if ~isempty(find(isnan(row_modes),1))
        disp('error in dim 1');
    end
    row_modes( isnan(row_modes) ) = 0;
    G(u,:,:) = permute(row_modes, [3 2 1]);
end
toc

%% 2-D EEMD    dim#2

D = zeros(sz(1), sz(2), goal+1, goal+1);

tic;
% time_pre = toc;
for m = 1:(goal+1)
    disp(['Solving mode ' num2str(m) '/' num2str(goal+1) ]);
    parfor v = 1:n2

        % solve and store
        col_modes = eemd(G(:,v,m)', goal, ens, nos_wn);
        if ~isempty(find(isnan(col_modes),1))
            disp('error in dim 2');
        end
        col_modes( isnan(col_modes) ) = 0;
        D(:,v,m,:) = permute(col_modes, [2 4 3 1]);
    end
end
toc

%% Combine modes

H = zeros(n1, n2, goal+1);
for m = 1:(goal+1)
    for k = m:(goal+1)
        H(:,:,m) = H(:,:,m) + D(:,:,m,k);
        H(:,:,m) = H(:,:,m) + D(:,:,k,m);
    end
    H(:,:,m) = H(:,:,m) - D(:,:,m,m);
end
% for m = (goal+1):-1:1
%     H(:,:,m) = sum( sum( D(:,:,m:end,m:end), 4), 3);
%     if m < (goal+1)
%         H(:,:,m) = H(:,:,m) - sum( H(:,:, (m+1):end ), 3);
%     end
% end
modes = H  .* std_img;

