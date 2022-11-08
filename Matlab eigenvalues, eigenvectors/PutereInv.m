function [valp vecp] = PutereInv(d, s, h, y, maxIter, tol)

n=length(d);

while maxIter>0;                    % Oprirea dupa un numar dat de iteratii.
  maxIter--;
     
   for i=1:n
     dd(i)=d(i)-h;                  % Deplasarea.
   endfor
   
   z=Thomas(s,dd,s,y);              % Rezolvarea sistemulul cu algoritmul Thomas.

 y=z/norm(z);                       
 vecp=y;                            % Actualizare vector propriu.
 
 h=Prod(d,s,y)'*y;
 valp=h;                            % Actualizare valoare proprie.
    
    if norm(Prod(d,s,y)-valp*y)<tol % Conditia de iesire.
      break;
    endif
      
endwhile

endfunction
