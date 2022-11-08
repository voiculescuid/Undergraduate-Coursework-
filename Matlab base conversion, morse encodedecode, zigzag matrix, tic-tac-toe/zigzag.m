function Z = zigzag(n)

%Initializare.

A=zeros(n);
count=0;

%Scrierea primelor n-1 diagonale secundare.
for i=2:n

  if mod(i,2) == 1
  
    for j=1:i-1
    A(j,i-j)=count;
    count=count+1;
    endfor
    
   else
   
     for k=1:i-1
     A(i-k,k)=count;
     count=count+1;
     endfor
     
   endif
   
endfor

%Rotirea maticeai penrtu scrierea ultimelor n-1 diagonale secundare in aceeasi maniera
%si initializarea inversa a contuarului.

count=n*n-1;
A=rot90(rot90(A));

%Scrierea ultimelor n-1 diagonale secundare.

for i=2:n

  if mod(i,2) == 1
  
    for j=1:i-1
    A(j,i-j)=count;
    count=count-1;
    endfor
    
   else
   
     for k=1:i-1
     A(i-k,k)=count;
     count=count-1;
     endfor
     
   endif
   
endfor

%Scrierea diagonalei principale.

A=rot90(A);
count=(n*n-n)/2;
if mod(n,2) == 0
  for l=n:-1:1
    A(l,l)=count;
    count=count+1;
  endfor
  else
   for l=1:n
    A(l,l)=count;
    count=count+1;
   endfor
endif

%Returnarea maticeai zigzag in forma normala.

Z=rot90(A);

endfunction
