function P = ValoriPolinoame(d, s, val_lambda)

P=zeros(1,length(d)+1);         % Preinitializare.
P(1)=1;                         % Prima si a doua valoare dupa care se calculeaza
P(2)=d(1)-val_lambda;           %urmatoarela valori recurent.

for i=3:length(d)+1
  P(i)=(d(i-1)-val_lambda)*P(i-1)-s(i-2)^2*P(i-2);    % Formula de recurenta pentru deterinarea valoriloar.
endfor

endfunction
