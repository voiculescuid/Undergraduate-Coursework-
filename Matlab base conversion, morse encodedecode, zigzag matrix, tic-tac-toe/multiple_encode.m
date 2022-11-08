function x = multiple_encode (str)

OK=0;

for i=1:length(str)
  enc=morse_encode(str(i));
   if OK == 0
    for j=1:length(enc)
    x(j)=enc(j);
    endfor
    OK=1;
   else
    for j=1:length(enc)
    x(j+div+2)=enc(j);
    endfor
   endif
div=length(x);
x(div+1)=' ';
endfor

endfunction
