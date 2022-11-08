function numvp = NrValProprii(d, s, val_lambda)

P=ValoriPolinoame(d,s,val_lambda);      % Vectorul care contine sirul Sturm.
numvp=0;        
semn1=0;                                % Valorile initiale pentru variabilele de semn si numarul de valori.
semn2=0;

  if P(1)<=0                            % Determinarea semnului primului element din sir.
   semn1=1;
  else
   semn1=-1;
  endif 

for i=2:length(P);                      
  if P(i)<0                              % Determinarea variabilei de semn pentru fiecare element din sirul Sturm.
   semn2=1;
  elseif P(1)==0                         % Tratarea cazului in care elementul este 0.
   semn2=-semn1;
  else
   semn2=-1;
  endif
 
  if semn1~=semn2                         % Contorizarea numarului de valori proprii.
    numvp=numvp+1;
  endif 
  
  semn1=semn2;                            % Actualizarea variabilei de semn pentru elementul predecesor.
endfor

endfunction
