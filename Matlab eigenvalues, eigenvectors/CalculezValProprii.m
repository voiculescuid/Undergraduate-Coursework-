function vp = CalculezValProprii(d, s, m, tol)
  
if m>length(d)                  %  In cazul in care m este mai mare decat numarul de
  m=length(d);                  %valori proprii, il actualizam.
endif

r = IntervaleValProprii(d, s, length(d));     % Vectorul de intervale.
vp=zeros(1,m);                                % Preinitializare vector valori proprii.

for i=1:m
  vp(i)=Bisectie(r(i),r(i+1),tol,d,s);             % Calcularea primelor m valori proprii cu ajutorul bisectiei.
endfor

endfunction
