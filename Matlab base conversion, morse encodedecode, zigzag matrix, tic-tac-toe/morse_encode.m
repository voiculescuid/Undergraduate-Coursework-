function x = morse_encode (c)

c=upper(c);

x=' ';
ro=['.' '-'];
map=['.' '.' '.' '.'];

while x==' ' 


for i = 1:2

if x ~=' '
break;
endif

for j = 1:2

if x ~=' '
break;
endif

for k = 1:2

if x ~=' '
break;
endif

for l = 1:2

if x ~=' '
break;
endif

mo = morse;

  for t = 1:length(map)   
    if map(t) == '.'
    mo = mo{2};
    
    elseif map(t) == '-'  
    mo = mo{3};
    endif
    
    if ~isempty(mo) && mo{1} == c
      for p=1:t
      x(p)=map(p);
      endfor
    break;
    endif
    
  endfor

  map(4)=ro(l);
  endfor
  map(3)=ro(k);
  endfor
  map(2)=ro(j);
  endfor 
  map(1)=ro(i);
  endfor
endwhile  

endfunction
