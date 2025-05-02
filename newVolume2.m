function generateCustomVolumes()
    % This function generates different types of 3D volumes and saves them as .mat files
    % Each function creates a different type of volumetric data

    % Set the dimension size for the volumes
    N = 256; % You can adjust this as needed
    
    % Generate different volumes
    generateSphereVolume(N, 'sphere_volume.mat');
    generateCubeVolume(N, 'cube_volume.mat');
    generateGaussianVolume(N, 'gaussian_volume.mat');
    generateSheppLoganPhantom(N, 'shepp_logan_volume.mat');
    generateMultiSphereVolume(N, 'multi_sphere_volume.mat');
    
    disp('All volumes generated successfully!');
end

function generateSphereVolume(N, filename)
    % Generate a 3D sphere
    r = zeros(N, N, N);
    center = N/2;
    radius = N/4;
    
    for i = 1:N
        for j = 1:N
            for k = 1:N
                % Calculate distance from center
                dist = sqrt((i-center)^2 + (j-center)^2 + (k-center)^2);
                % If inside the sphere
                if dist <= radius
                    r(i,j,k) = 255;
                end
            end
        end
    end
    
    % Save the volume
    save(filename, 'r');
    disp(['Saved ' filename]);
end

function generateCubeVolume(N, filename)
    % Generate a 3D cube
    r = zeros(N, N, N);
    center = N/2;
    size = N/4;
    
    r(center-size:center+size, center-size:center+size, center-size:center+size) = 255;
    
    % Save the volume
    save(filename, 'r');
    disp(['Saved ' filename]);
end

function generateGaussianVolume(N, filename)
    % Generate a 3D Gaussian
    r = zeros(N, N, N);
    center = N/2;
    sigma = N/8;
    
    for i = 1:N
        for j = 1:N
            for k = 1:N
                % Calculate Gaussian function value
                r(i,j,k) = 255*exp(-((i-center)^2 + (j-center)^2 + (k-center)^2) / (2*sigma^2));
            end
        end
    end
    
    % Save the volume
    save(filename, 'r');
    disp(['Saved ' filename]);
end

function generateSheppLoganPhantom(N, filename)
    % Generate a 3D Shepp-Logan phantom (commonly used in 3D tomography)
    % This function requires the Image Processing Toolbox
    try
        % Check if phantom3 is available (requires Image Processing Toolbox)
        if exist('phantom3', 'file')
            r = phantom3('Modified Shepp-Logan', N);
        else
            % Create a basic 3D phantom manually if the function is not available
            r = generateBasicPhantom(N);
        end
        
        % Save the volume
        save(filename, 'r');
        disp(['Saved ' filename]);
    catch e
        disp(['Error generating Shepp-Logan phantom: ' e.message]);
        disp('Using basic phantom instead');
        generateBasicPhantom(N, filename);
    end
end

function r = generateBasicPhantom(N)
    % Generate a basic phantom with ellipsoids if phantom3 is not available
    r = zeros(N, N, N);
    center = N/2;
    
    % Add a large ellipsoid for the head
    for i = 1:N
        for j = 1:N
            for k = 1:N
                % Calculate ellipsoid
                val = ((i-center)/(N/2.5))^2 + ((j-center)/(N/2.5))^2 + ((k-center)/(N/3))^2;
                if val <= 1
                    r(i,j,k) = 0.5;
                end
            end
        end
    end
    
    % Add some smaller ellipsoids for internal structures
    for i = 1:N
        for j = 1:N
            for k = 1:N
                % Small ellipsoid 1
                val1 = ((i-center)/(N/10))^2 + ((j-center+N/8)/(N/10))^2 + ((k-center)/(N/6))^2;
                % Small ellipsoid 2
                val2 = ((i-center)/(N/10))^2 + ((j-center-N/8)/(N/10))^2 + ((k-center)/(N/6))^2;
                
                if val1 <= 1
                    r(i,j,k) = 1;
                elseif val2 <= 1
                    r(i,j,k) = 0.8;
                end
            end
        end
    end
    
    return;
end

function generateMultiSphereVolume(N, filename)
    % Generate multiple spheres of different sizes
    r = zeros(N, N, N);
    center = N/2;
    
    % Sphere positions and radii
    positions = [
        center, center, center;
        center+N/4, center+N/4, center;
        center-N/4, center-N/4, center;
        center+N/4, center-N/4, center+N/4;
        center-N/4, center+N/4, center-N/4;
    ];
    
    radii = [N/6, N/10, N/8, N/12, N/9];
    
    for s = 1:size(positions, 1)
        pos = positions(s,:);
        radius = radii(s);
        
        for i = 1:N
            for j = 1:N
                for k = 1:N
                    % Calculate distance from center of this sphere
                    dist = sqrt((i-pos(1))^2 + (j-pos(2))^2 + (k-pos(3))^2);
                    % If inside the sphere
                    if dist <= radius
                        r(i,j,k) = s/size(positions, 1); % Different intensity for each sphere
                    end
                end
            end
        end
    end
    
    % Save the volume
    save(filename, 'r');
    disp(['Saved ' filename]);
end

function generateCustomPatternVolume(N, filename)
    % Generate a custom pattern volume with specific features
    r = zeros(N, N, N);
    center = N/2;
    
    % Add a gradient along x-axis
    for i = 1:N
        gradientValue = i/N;
        for j = 1:N
            for k = 1:N
                % Create a pattern with rings
                dist = sqrt((j-center)^2 + (k-center)^2);
                ringPattern = sin(dist/10)^2;
                
                % Combine gradient and ring pattern
                r(i,j,k) = gradientValue * ringPattern;
            end
        end
    end
    
    % Save the volume
    save(filename, 'r');
    disp(['Saved ' filename]);
end

% Replace this with your desired path
absolutePath = '/home/rick/Desktop/2Dprojection/volume.mat';

% generateGaussianVolume(256, absolutePath);
% generateCustomPatternVolume(256, absolutePath)
generateCubeVolume(256, absolutePath);