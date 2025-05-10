function [sliceData] = ExtractSliceFromUnifiedVolume(volume, N, rotationVector, angle)
    % Create meshgrid for the volume
    meshN = -(N / 2):1:(N / 2) - 1;
    [x, y, z] = meshgrid(meshN, meshN, meshN);
    
    % Create a grid for the slice (initially in xy-plane, z=0)
    [xGrid, yGrid] = meshgrid(meshN, meshN);
    zGrid = zeros(size(xGrid));
    
    % Convert angle to radians
    angleRad = angle * pi / 180;
    
    % Normalize the rotation vector
    rotationVector = rotationVector / norm(rotationVector);
    vx = rotationVector(1);
    vy = rotationVector(2);
    vz = rotationVector(3);
    
    % Initialize rotated slice coordinates
    xRot = zeros(size(xGrid));
    yRot = zeros(size(yGrid));
    zRot = zeros(size(zGrid));
    
    % Rodrigues' rotation formula implementation
    cosTheta = cos(angleRad);
    sinTheta = sin(angleRad);
    
    % Apply rotation to each point in the slice
    for i = 1:size(xGrid, 1)
        for j = 1:size(xGrid, 2)
            % Original point
            x0 = xGrid(i, j);
            y0 = yGrid(i, j);
            z0 = zGrid(i, j);
            
            % Dot product with rotation axis
            dotProduct = vx*x0 + vy*y0 + vz*z0;
            
            % Cross product with rotation axis
            crossX = vy*z0 - vz*y0;
            crossY = vz*x0 - vx*z0;
            crossZ = vx*y0 - vy*x0;
            
            % Apply Rodrigues' rotation formula
            xRot(i, j) = x0*cosTheta + crossX*sinTheta + vx*dotProduct*(1-cosTheta);
            yRot(i, j) = y0*cosTheta + crossY*sinTheta + vy*dotProduct*(1-cosTheta);
            zRot(i, j) = z0*cosTheta + crossZ*sinTheta + vz*dotProduct*(1-cosTheta);
        end
    end
    
    % Initialize the slice data
    sliceData = zeros(size(xRot));
    
    % Perform trilinear interpolation to extract the slice data
    for i = 1:size(xRot, 1)
        for j = 1:size(xRot, 2)
            % Get the coordinates in the volume space
            xp = xRot(i, j) + N/2;
            yp = yRot(i, j) + N/2;
            zp = zRot(i, j) + N/2;
            
            % Ensure coordinates are within bounds
            if xp < 1, xp = 1; end
            if yp < 1, yp = 1; end
            if zp < 1, zp = 1; end
            if xp > N, xp = N; end
            if yp > N, yp = N; end
            if zp > N, zp = N; end
            
            % Get integer indices and fractional parts
            x0 = floor(xp);
            y0 = floor(yp);
            z0 = floor(zp);
            
            % Handle edge case
            if x0 == N, x0 = N-1; end
            if y0 == N, y0 = N-1; end
            if z0 == N, z0 = N-1; end
            
            xd = xp - x0;
            yd = yp - y0;
            zd = zp - z0;
            
            % Get the eight corner values
            c000 = volume(y0, x0, z0);
            c001 = volume(y0, x0+1, z0);
            c010 = volume(y0+1, x0, z0);
            c011 = volume(y0+1, x0+1, z0);
            c100 = volume(y0, x0, z0+1);
            c101 = volume(y0, x0+1, z0+1);
            c110 = volume(y0+1, x0, z0+1);
            c111 = volume(y0+1, x0+1, z0+1);
            
            % Perform trilinear interpolation
            c00 = c000*(1-xd) + c001*xd;
            c01 = c010*(1-xd) + c011*xd;
            c10 = c100*(1-xd) + c101*xd;
            c11 = c110*(1-xd) + c111*xd;
            
            c0 = c00*(1-yd) + c01*yd;
            c1 = c10*(1-yd) + c11*yd;
            
            sliceData(i, j) = c0*(1-zd) + c1*zd;
        end
    end
    
    % Remove NaN values (replace with 0)
    sliceData(isnan(sliceData)) = 0;
end