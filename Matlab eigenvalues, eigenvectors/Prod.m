function x = Prod (d,s,y)

n=length(d);

x(1)=d(1)*y(1)+s(1)*y(2);                     % Inmultirea primei linii cu vectorul y.
x(n)=s(n-1)*y(n-1)+d(n)*y(n);                 % Inmultirea ultimei linii cu vectorul y.              

for i=2:n-1
  x(i)=s(i-1)*y(i-1)+d(i)*y(i)+s(i)*y(i+1);   % Inmultirea liniilor 2:n-1 cu vectorul y.
endfor

  x=x';                                       % Returnarea vectorului coloana rezultat.
endfunction
