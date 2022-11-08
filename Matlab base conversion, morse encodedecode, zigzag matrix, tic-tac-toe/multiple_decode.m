function x = multiple_decode (sir) 

OK=0;
div=0;
sir(length(sir)+1)=' ';
car=' ';
for i=1:length(sir)

count=1;

  if sir(i) == ' '
  car=[];
    for j=div+1:i-1
    car(count)=sir(j);
    count=count+1;
    endfor
      OK=OK+1;
  div=i;
  
  x(OK)=morse_decode(car);
  
  endif
  
endfor

endfunction
