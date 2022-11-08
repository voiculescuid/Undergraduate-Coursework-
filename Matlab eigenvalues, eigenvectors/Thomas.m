function x = Thomas(a, b, c, d)
	n = length(d);
 
  %Transform a astfel incat sa aiba n elemente, cu primul element 0.
 	for i=1:length(a);
    aux(i+1)=a(i);
  endfor
  aux(1)=0;
  
  a = aux;

	% Operatiile la limita.
	c(1) = c(1)/b(1); 
	d(1) = d(1)/b(1);   
 	
 	% Calculul coeficientilor pe caz general.
	for i = 2 : n-1
		temp = b(i)-a(i)*c(i-1);
		c(i) = c(i)/temp;
		d(i) = (d(i)-a(i)*d(i-1))/temp;
	endfor
	d(n) = (d(n)-a(n)*d(n-1))/(b(n)-a(n)*c(n-1));
 
	% Substitutia inapoi pentru rezolvarea sistemului de ecuatii.
	x(n) = d(n);
	for i = n-1 : -1 : 1
		x(i) = d(i)-c(i)*x(i+1);
	endfor
  x=x';
endfunction