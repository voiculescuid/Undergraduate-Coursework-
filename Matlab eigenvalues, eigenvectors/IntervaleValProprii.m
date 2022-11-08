function r = IntervaleValProprii(d, s, m)
  
OK=0;
if m>length(d)                      %  In cazul in care m este mai mare decat numarul de
  m=length(d);                      %valori proprii, il actualizam.
endif

numvp = 0;

r=zeros(1,m+2);                     % Preinitializare vector intervale.

[inf sup] = LimiteValProprii(d,s);  %
                                    %   Initializarea limite in care sunt cuprinse
r(1)=inf;                           %toate valorile proprii.
r(m+2)=sup;                         %

for k=m:-1:1                        %
                                    %
  mij=(r(k+2)+r(1))/2;              %
  h=r(k+2)-mij;                     %
                                    %
                                    %
    while (numvp ~=k)               %  
  numvp = NrValProprii(d,s,mij);    %  Determinarea intervalelor pentru valori proprii
  h=h/2;                            %comform indicatiilor date.
  if numvp<k;                       %
    mij=mij+h;                      %
  elseif numvp>k                    %
    mij=mij-h;                      %
  endif                             %
    endwhile                        %
                                    %
   r(k+1)=mij;                      %
                                    %
endfor                              %

r(m+2)=[];                          % Eliminarea limitei superioare din vector.

endfunction
