function image = processImage(array)
  maxBlack = 200;
  pixel = 1;
  image = array;
  while(pixel <= size(array,2))
    if (array(pixel) <= maxBlack)
      image(pixel) = 0;
    endif
    pixel++;
  endwhile
  