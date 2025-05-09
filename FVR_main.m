% Set cube size
N = 256;  % You can change this as needed

% Generate a 3D cube directly
r = zeros(N, N, N);
center = N/2;
cube_size = N/4;

r(center - cube_size : center + cube_size, ...
  center - cube_size : center + cube_size, ...
  center - cube_size : center + cube_size) = 255;

% 3D FFT-shift for the spatial volume
volume = fftshift(r);

% Compute the 3D Spectrum 
spectrum = fftn(volume);  % Use fftn for 3D FFT

% Do a fft shift 
spectrum = fftshift(spectrum);

% Split the volume into real and imaginary components
[realVolume, imagVolume] = SplitComplexVolume(spectrum, N, N, N);

% Initialize containers
snps = cell(1, 1001); 
counterC = 1;
ps = cell(1, 1001); 
counterA = 1;

% Tilt axis
pivot = [0.70710678118, 0.70710678118, -1];

% Loop over tilt angles
for angle = -90:15:90
    % Extract the projection slice 
    projectionSlice = ExtractProjectionSliceFromUnifiedVolume(realVolume, imagVolume, N, pivot, angle);
    
    % Backtransform the slice to spatial domain and apply 2D FFT shift
    projection = fftshift(abs(ifft2(projectionSlice)));
    
    % Format angle string for filename
    angleStr = sprintf('%+06.2f', angle);  % Format: +00.00 or -00.00
    pureFilename = sprintf('/home/rick/Desktop/2Dprojection/pure_projection_%s.png', angleStr);
    
    % Save the image
    imwrite(projection * 1e-3, pureFilename);
end
