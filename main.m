% Set cube size
N = 64;  % You can change this as needed

% Define the pivot for rotation stuff
pivot = [1, -2, -1];

% Code to initilaize the volume information for the main rendering
[realVolume, imagVolume] = initialize_main(N);

% Loop over tilt angles
for angle = -90:15:90
    % By reusing the frequency for each rendering we cut alot of processing done
    one_run_main(realVolume, imagVolume, N, pivot, angle);
end