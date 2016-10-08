
pixel = 0;

while (pixel <= 128)
  imagemInicial = sin(pixel *(pi/128));
  
  imagem(pixel + 1) =  255 + 255 * (cos((pixel * (pi/128)) + (pi/2)));
  
  pixel++;
  
  endwhile
  
plot(imagem);