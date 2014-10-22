% pure EMD, an implementation of HHT
% coded by Po-Nan Li @ Inst. of Phys., Academia Sinica, Taiwan

function c = emd(y, goal)
%%

sz = length(y);
t = 1:sz;

%% Solve EMD

c = zeros(goal+1,sz);
h = y;
r = h;
for m = 1:goal
    count = 0;
    unsolved = 1;
    h = r;
%     while(unsolved)
    while(count < ceil(sqrt(sz)))        
        
        count = count + 1;
%         disp([num2str(count) 'th trial for solving mode ' num2str(m)]);
        [mx_p, mx_v, mn_p, mn_v] = find_extrema(h);
%         [mx_p, mx_v, mn_p, mn_v] = find_extrema(h);
%         if length(mx_p)<3 || length(mn_p)<3
%             break;
%         end
        % interpolate by spline
        m1_mx = spline(t(mx_p), mx_v, t);
        m1_mn = spline(t(mn_p), mn_v, t);
        m1_av = (m1_mx + m1_mn) ./ 2;
        h = h - m1_av;
        % check if IMF
%         zx = zerox(h);
%         [hmx_p, hmx_v, hmn_p, hmn_v] = cextrema(h);
% %         [hmx_p, hmx_v, hmn_p, hmn_v] = find_extrema(h);
%         h_mx = length(hmx_p);
%         h_mn = length(hmn_p);
%         if length(hmx_p)<3 || length(hmn_p)<3
%             break;
%         end
%         h1_mx = cspline(t(hmx_p), hmx_v, t);
%         h1_mn = cspline(t(hmn_p), hmn_v, t);
% 
%         h1_av = (h1_mx + h1_mn) ./ 2;
% %         disp(['max ' num2str(h_mx) ', min ' num2str(h_mn)...
% %             ', zero-x ' num2str(zx)]);
% %         disp(['normalized mean ' num2str(mean(abs(m1_av./std(h1_av))))]);
%         if (mean(abs(h1_av./std(h1_av))) < 0.5) || (count > 11)
%             if (abs(h_mx+h_mn-zx) < 6) % including 4 additional ending points
%                 unsolved = 0;
%             end
%         end
    end
    r = r - h;
    c(m,:) = h;
    
%     h = r;
end

%%
c(end,:) = r;
