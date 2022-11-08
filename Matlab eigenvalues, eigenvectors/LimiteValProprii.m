function [limita_inf, limita_sup] = LimiteValProprii(d, s)

t=zeros(1,length(d));                       % Preinitializare.
limita_inf=realmax;
limita_sup=-realmax;

for i=1:length(d)                           % 
  for j=1:length(d)                         %
                                            %
    if j==i+1                               %
    t(i)=t(i)+abs(s(i));                    %
    elseif i==j+1                           %
    t(i)=t(i)+abs(s(j));                    %
    endif                                   %
                                            %
   endfor                                   %   Teorema lui Gershgorin
endfor                                      %
                                            %
for i=1:length(d)                           %
                                            %        
  limita_inf=min(limita_inf, (d(i)-t(i)));  %
                                            %
  limita_sup=max(limita_sup, (d(i)+t(i)));  %
                                            %
endfor                                      %

endfunction
