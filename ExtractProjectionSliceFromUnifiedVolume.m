
function [complexSlice] = ExtractProjectionSliceFromUnifiedVolume ... 
                          (realVolume, imagVolume, N, rotationVector, angle)
                      
realData = ExtractSliceFromUnifiedVolume ...
                                    (realVolume, N, rotationVector, angle);
imagData = ExtractSliceFromUnifiedVolume ...
                                    (imagVolume, N, rotationVector, angle);

% Build the complex slice
complexSlice = zeros(N, N);
for ii = 1:1:N
    for jj = 1:1:N
        complexSlice(ii,jj) = (realData(ii, jj)) + (imagData(ii, jj))* 1i;
    end
end

end
