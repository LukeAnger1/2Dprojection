function [projection] = one_run_main(realVolume, imagVolume, N, pivot, angle)

        % Extract the projection slice 
        projectionSlice = ExtractProjectionSliceFromUnifiedVolume(realVolume, imagVolume, N, pivot, angle);
        
        % Backtransform the slice to spatial domain and apply 2D FFT shift
        projection = fftshift(abs(ifft2(projectionSlice)));
        
        % Format angle string for filename
        angleStr = sprintf('%+06.2f', angle);  % Format: +00.00 or -00.00
        pureFilename = sprintf('/home/rick/Desktop/2Dprojection/data/3. rotating cube with face/pure_projection_%s.png', angleStr);
        
        % stupid scaling
        projection = projection * 1e-3;

        % Save the image
        imwrite(projection, pureFilename);
end