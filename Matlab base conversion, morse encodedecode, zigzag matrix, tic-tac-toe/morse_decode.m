function x = morse_decode (sir)

%Apelarea functiei de generarea al cell array pentru codul morse.

mo = morse;

%Functie care parcurge arborele binar pe cel mult 4 nivele.

if length(sir)<5
  for k = 1:length(sir)   %Pentru fiecare punct se inainteaza in arbore spre stanga.
    if sir(k) == '.'
    mo = mo{2};
    
    elseif sir(k) == '-'  %Pentru fiecare linie se inainteaza in arbore spre dreapta.
    mo = mo{3};
    endif
    
  endfor
      
      %Cand s-a terminat parcurgerea, in cazul in care s-a ajuns intr-un nod in care nu exista 
%caracter se returneaza '*', in caz contrar se returneza caracterul respectiv.
      
    if isempty(mo)
    x = '*';
    else
    x = mo{1};
    endif
    
 else
 x = '*';   %Se returneaza '*' in cazul in care sirul are lungimea este mai mare de 4.
 endif
    
endfunction
