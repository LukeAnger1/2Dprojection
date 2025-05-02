% Loading the volume data from the RAW file 
load('volume.mat');
N = size(r,1);
% % 3D FFT-shift for the spatial volume
volume = fftshift(r);
%Compute the 3D Spectrum 
spectrum = fft3(volume); 
%Do a fft shift 
spectrum = fftshift(spectrum);
%Split the volume to the two components real and imaginary, and fine the
%projection slice for every component.
[realVolume, imagVolume] = SplitComplexVolume(spectrum, N, N, N);
snps= cell(1,1001); 
counterC = 1 ;
ps= cell(1,1001); 
counterA = 1 ;
%Tilt axis : in this case y axis
pivot = 'Y';
for angle = -90:15:90
    % Extract the projection slice 
    projectionSlice = ExtractProjectionSliceFromUnifiedVolume ... 
                                (realVolume, imagVolume, N, pivot, angle);
    % Backtransforming the slice to the spatial domain to yield the 
    % projection followed by 2D FFT-shift for the projection. 
    projection = fftshift(abs(ifft2(projectionSlice)));
    %adding noise using agwn function
    NoisyProjectionY = awgn(projection,15,'measured'); 
    %shifting the projection by adding a random number between [ 0.01]
    ShiftedNoisyProjectionY = NoisyProjectionY + ((0.01).*rand(1));
    %scale projection in coordinate
    ShiftedNoisyProjectionscale = (NoisyProjectionY + ((0.01).*rand(1)))* 1e-3;
    snps{counterC} = ShiftedNoisyProjectionscale;
    counterC = counterC +1 ;
    %correcting the scale of representing
    ps{counterA} = projection*1e-3;
    counterA = counterA +1 ;
    
    % Generate a filename with the angle value
    % Convert angle to string with proper formatting
    angleStr = sprintf('%+06.2f', angle); % Format: +00.00 or -00.00
    
    % Display figures
    figure(1);
    figure(2);
    subplot(1,2,1),imshow((projection)* 1e-3),title('Pure Projections');
    subplot(1,2,2),imshow(ShiftedNoisyProjectionscale),title('SN Projections');

    % Save each projection with unique filenames including the angle
    pureFilename = sprintf('/home/rick/Desktop/2Dprojection/pure_projection_%s.png', angleStr);
    noisyFilename = sprintf('/home/rick/Desktop/2Dprojection/noisy_projection_%s.png', angleStr);
    
    imwrite(projection*1e-3, pureFilename);
    imwrite(ShiftedNoisyProjectionscale, noisyFilename);
     
end
save(['snps','.mat'],'snps');
save(['ps','.mat'],'ps'); % Also save the pure projections