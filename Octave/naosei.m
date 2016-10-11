function image = naosei(vetor)
  i = 2;
  max =1;
  while (i <= 128)
    if (vetor(i) > vetor(max))
      max = i;
     endif
     i++;
  endwhile
  display("Maximo: ");
  display(max);
  i = 1;
  maxP = 0.1;
  
  while (i < max)
    if (vetor(i) > maxP)
      maxP = vetor(i);
    endif
    
    if ((vetor(i)/maxP) < 0.85 && i != 1)
      display("Posicao:");
      display(i);
    endif
    i++;
    
  endwhile
  i = max;
  while (i <= 128)
    if (vetor(i) > maxP)
      maxP = vetor(i);
    endif
    
    if ((vetor(i)/maxP) < 0.85 && i != 1)
      display("Posicao:");
      display(i);
    endif
    i++;
    
  endwhile