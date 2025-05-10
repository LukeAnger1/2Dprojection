function [projection] = one_run_main(realVolume, imagVolume, N, pivot, angle)

        % Extract the projection slice 
        projectionSlice = ExtractProjectionSliceFromUnifiedVolume(realVolume, imagVolume, N, pivot, angle);
        
        % Backtransform the slice to spatial domain and apply 2D FFT shift
        projection = fftshift(abs(ifft2(projectionSlice)));
        
        % stupid scaling
        projection = projection * 1e-3;

end