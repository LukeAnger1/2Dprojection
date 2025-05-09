function [realVolume, imagVolume] = initialize_main (N)

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
end