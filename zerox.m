function count = zerox(y)
m = length(y);
count = length(find(y(1:(m-1)).*y (2:m) <0));
end