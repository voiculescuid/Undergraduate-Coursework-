function p = Bisectie(a,b,tol,d,s)

fa=ValoriPolinoame(d, s, a);
fb=ValoriPolinoame(d, s, b);

nr=length(d)+1;

if fa(nr)*fb(nr)>0 
    p=0;
    
else
    p = (a + b)/2;
    fp=ValoriPolinoame(d, s, p);
    
    while abs(fp(nr)) > tol && abs(b-a)>tol
      
      if fa(nr)*fp(nr)<0 
         b = p;
      else
         a = p;          
      endif
   
      p = (a + b)/2; 
      fp=ValoriPolinoame(d, s, p);
      fa=ValoriPolinoame(d, s, a);
      fb=ValoriPolinoame(d, s, b);
    
    endwhile
endif

endfunction