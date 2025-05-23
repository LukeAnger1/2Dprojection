
function [sliceData] = ExtractSliceFromUnifiedVolume ...
                                        (volume, N, rotationVector, angle)

% Construct the mesh grid for sampling the volume 
meshN = -(N / 2):1:(N / 2) - 1;
[x, y, z] = meshgrid(meshN, meshN, meshN);

% Build a surface with size equal to the final slice size
% NOTE: This function assumes a unified volume. 
sliceExtent = linspace(-N / 2, N / 2 , N);
figure(1);
slicePlane = surf(sliceExtent, sliceExtent, zeros((N), (N)));
% Adjust the rotation of the slice through the volume. 
% By defult, it assumes a Y-axis rotation
rotate(slicePlane, rotationVector, angle);

% Get the slice indexes.
xData =  get(slicePlane,'XData');
yData =  get(slicePlane,'YData');
zData =  get(slicePlane,'ZData');
% Free the slice plane 
delete(slicePlane); 
% Return the intersection between the volume and the slice after the
% interpolation.
sliceHdl = slice(x, y, z, volume, xData, yData, zData);
sliceData = get(sliceHdl, 'CData');
axis tight ;
grid on, shading interp;
% Remove all the nan's/
sliceData(isnan(sliceData)) = 0;

end
