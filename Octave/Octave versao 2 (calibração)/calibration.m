function parameterArray = calibration(array)
  pixel = 1;
  
  while (pixel <=size(array,2))
    parameterArray(pixel) = 255 - array(pixel);
    pixel++;
  endwhile