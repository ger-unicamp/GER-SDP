% Limpa as variaveis e a Janela de Comandos.
clear; clc;

% Digite aqui o nome da porta que sera utilizada.
PORTA = "/dev/ttyACM0";

% Escolha o modo de operacao desejado:
% Digite (1): Para exibir a imagem digital da camera.
% Digite (2): Para exibir o grafico em tempo real dos pixels da camera.
% Digite (3): Para imprimir o vetor de pixels na Janela de Comandos.
COMANDO = 2;

pkg load instrument-control;

% Cria um objeto para comunicao serial.
s = serial(PORTA);

% Tempo limite de espera pela informacao.
set (s, 'timeout', 2);

% Delay de segurança para iniciar a comunicao.
pause(1);

% Testa se o serial esta ok.
if (exist("serial") != 3)  disp("Serial: Unsupported") endif

fopen(s);

srl_flush(s);
% Variaveis de controle.
counter = 1;
digit = 2;
number = 0;
read = false;
vetor = 0;
calib = false;
correcao = 0;

while true
  % Realiza a leitura.
  in = srl_read(s,1);
  
  % Nao salva as leituras enquanto nao acha o comeco do vetor.
  if (!read)
    % Enquanto in eh diferente de '\n'.
    while (in != 10)
      in = srl_read(s,1);
    endwhile
    % Descarta o "carriage return";
    srl_read(s,1);
    read = true;
  
  % Encontrou um ' ' (espaço)
  elseif (in == 32)
    % A proxima leitura ira ler o primeiro digito do numero (digito 2).
    digit = 2;
    number = 0;
  
  % Verifica se '\n'
  elseif (in == 10)
    % Descarta o "carriage return";
    srl_read(s,1);
    
    % Tratamento da imagem
    %if (calib == false)
     % correcao = calibration(vetor)
      %imagem = correcao + vetor;
      %calib = true;
    %endif
    
    %imagem = correcao + vetor;
    
    %imagem = processImage(imagem);
    imagem = vetor;
      
    %image = vetor;
    % Exibe a imagem digital da camera.
    if (COMANDO == 1)
      im = imagem / 4;
      image(im);
      colormap(gray);
      pause(0.01);
      
    % Exibe o grafico em tempo real dos pixels da camera.
    elseif (COMANDO == 2)
      %plot(imagem);
      plot(vetor);
      pause(0.01);
      
    % Imprime o vetor de pixels na Janela de Comandos.
    elseif (COMANDO == 3)
      disp(imagem);
      pause(1);
    
    else display("Modo de operacao invalido!");
    endif
    
    % Limpa o vetor e o seu contador.
    vetor = 0;
    counter = 1;
    
  % Encontrou uma parte de um numero
  else
  
    % Conversao para decimal
    in = in - 48;
    
    % Primeiro digito do numero (centena).
    if (digit == 2)
      number = (in * 100);
      digit = 1;
      
    % Segundo digito do numero (dezena).
    elseif (digit == 1)
      number = number + (in * 10);
      digit = 0;
      
     % Terceiro digito do numero (unidade). 
    elseif (digit == 0)
      number = number + in;
      vetor(counter) = number;
      counter++;
      
    endif
    
  endif
  
endwhile
  
fclose(s)
