
function r = baza(sursa,b1,b2)
  
  nr=0;
  car='0123456789abcdefghijklmnopqrst';
  len=length(sursa);
  
  if b1<2 || b1>30
    error('B1 trebuie sa fie cuprinsa intre 2 si 30.');     %Se verifica daca baza "b1" este valida.
  endif

  if b2<2 || b2>30
    error('B2 trebuie sa fie cuprinsa intre 2 si 30.');     %Se verifica daca baza "b2" este valida.
  endif
  
  for i=2:len
   for j=(b1+1):30
     if sursa(i) == car(j)
         error('Numar invalid in baza b1.');                %Verificare ca 'sursa' sa contina caractere valide in baza data.
     endif
   endfor
 endfor
  
%Transformarea din baza 'b1' in zecimal.
  
  for i=1:len
    for j=1:b1
      if sursa(i) == car(j)
        nr=nr+(j-1)*b1^(len-i);
      endif
    endfor
  endfor
  
nr2=nr;
len2=0;

%Numarul de caractere care o sa il aibe 'sursa' in baza "b2".

while nr2>1
  nr2=nr2/b2;
  len2=len2+1;
  endwhile

%Transformare din zecimal in baza "b2".
  
for i=1:len2
  m=mod(nr,b2);
  tr(len2-i+1)=car(m+1);
  nr=(nr-mod(nr,b2))/b2;
endfor

r=tr;

endfunction
