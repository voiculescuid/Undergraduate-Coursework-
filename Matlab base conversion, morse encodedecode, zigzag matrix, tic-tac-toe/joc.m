

function [] = joc ()
   
%Initializarea tabelei de scor si a conditiei de joc.   
   
   CONT(1)=0;
   CONT(2)=0;
   CON='y';
   
   while CON == 'y'
   
%Alegerea la inceput de joc a utilizatorului pentru caracterul cu care va joca ( x sau 0).
   
      a = input('X sau O?:','c');
   co='-';
   if strcmp(a,'x')!=1 && strcmp(a,'X')!=1 && strcmp(a,'0')!=1
     error('Just x or 0!');
   endif
   
   if strcmp(a,'x') || strcmp(a,'X')
     b='0';
     else
     b='x';
   endif
   
%Initializarea matricei de joc, si afisarea tabelui pe care se vor face mutarile.
   
     for i=1:3
     for j=1:3
       A(i,j)=co;
     endfor
   endfor
   
      printf('      1     2    3\n');
   printf('    _________________\n');
   printf('   |     |     |     |\n');
   printf('1  |  %c  |  %c  |  %c  |\n',A(1,1),A(1,2),A(1,3));
   printf('   |_____|_____|_____|\n');
   printf('   |     |     |     |\n');
   printf('2  |  %c  |  %c  |  %c  |\n',A(2,1),A(2,2),A(2,3));
   printf('   |_____|_____|_____|\n');
   printf('   |     |     |     |\n');
   printf('3  |  %c  |  %c  |  %c  |\n',A(3,1),A(3,2),A(3,3));
   printf('   |_____|_____|_____|\n');
   printf('\n');
   printf('Inserarea se face introducand coordonatele casutei.\n');
   
   won=-1;    %Conditia de joc a unei partide.
 
 
 while won==-1
   
 
%Intruducerea pozitiei de inserarea de cartre utilizator.
%In cazul in care se insereaza caracterul 'q' se iese din partide de joc si se interogheaza cu continuare sau exit.
%
 
 
        ax = input('Abscisa:','%d');
   
   if strcmp(ax,'q')
     break;
   endif
        
        ay = input('Ordonata:','%d');
   
   if strcmp(ay,'q')
     break;
   endif
        
        ax=str2num(ax);
        ay=str2num(ay);
     OK2=0;
        while (OK2==0)
        if strcmp(A(ax,ay),co)
            A(ax,ay)=a;
          OK2=1;
          else
          printf('Miscare invalida\n');
          printf('introduceti o noua pozitie:\n');
          ax = input('Abscisa:','%d');
          ay = input('Ordonata:','%d');
          ax=str2num(ax);
          ay=str2num(ay);
        endif
        endwhile
%

%Un algoritm destul de costisitor cu o eficienta scazuta dupa care se va face mutarea calculatorului.
        
        %linii
        if (A(1,1) == A(1,2) && A(1,1) ==b )
        A(1,3)=b;
        elseif (A(2,1) == A(2,2) && A(2,1) ==b && A(2,3) == co)
        A(2,3)=b;
        elseif (A(3,1) == A(3,2) && A(3,1) ==b && A(3,3) == co)
        A(3,3)=b;
        elseif (A(1,3) == A(1,2) && A(1,3) ==b && A(1,1) == co)
        A(1,1)=b;
        elseif (A(2,3) == A(2,2) && A(2,3) ==b && A(2,1) == co)
        A(2,1)=b;
        elseif (A(3,3) == A(3,2) && A(3,3) ==b && A(3,1) == co)
        A(3,1)=b;
        
        elseif (A(1,1) == A(1,3) && A(1,1) == b && A(1,2) == co)
        A(1,2)=b;
        elseif (A(2,1) == A(2,3) && A(2,1) == b && A(2,2) == co)
        A(2,2)=b;
        elseif (A(3,1) == A(3,3) && A(3,1) == b && A(3,2) == co)
        A(3,2)=b;
        
        %coloane
        elseif strcmp(A(1,1),A(2,1)) && strcmp(A(1,1),b) && strcmp(A(3,1),co)
        A(3,1)=b;
        elseif (A(1,2) == A(2,2) && A(1,2) ==b && A(3,2) == co)
        A(3,2)=b;
        elseif (A(1,3) == A(2,3) && A(1,3) ==b && A(3,3) == co)
        A(3,3)=b;
        elseif (A(3,1) == A(2,1) && A(3,1) ==b && A(1,1) == co)
        A(1,1)=b;
        elseif (A(3,2) == A(2,2) && A(3,2) ==b && A(1,2) == co)
        A(1,2)=b;
        elseif (A(3,3) == A(2,3) && A(3,3) ==b && A(1,3) == co)
        A(1,3)=b;
        
        elseif (A(1,1) == A(3,1) && A(1,1) ==b && A(2,1) == co)
        A(2,1)=b;
        elseif (A(1,2) == A(3,2) && A(1,2) ==b && A(2,2) == co)
        A(2,2)==b;
        elseif (A(1,3) == A(3,3) && A(1,3) ==b && A(2,3) == co)
        A(2,3)=b;
        
        %diagonale
        elseif (A(1,1) == A(2,2) && A(1,1) == b && A(3,3) == co)
        A(3,3)=b;
        elseif (A(3,3) == A(2,2) && A(3,3) == b && A(1,1) == co)
        A(1,1)=b;
        elseif (A(1,3) == A(2,2) && A(1,3) == b && A(3,1) == co)
        A(3,1)=b;
        elseif (A(3,1) == A(2,2) && A(3,1) == b && A(1,3) == co)
        A(1,3)=b;
        
        elseif (A(1,1) == A(3,3) && A(1,1) == b && A(2,2) ==co)
        A(2,2)=b;
        elseif (A(1,3) == A(3,1) && A(1,3) == b && A(2,2) ==co)
        A(2,2)=b;
        
        %linii inverse
        elseif (A(1,1) == A(1,2) && A(1,1) ==a && A(1,3) == co)
        A(1,3)=b;
        elseif (A(2,1) == A(2,2) && A(2,1) ==a && A(2,3) == co)
        A(2,3)=b;
        elseif (A(3,1) == A(3,2) && A(3,1) ==a && A(3,3) == co)
        A(3,3)=b;
        elseif (A(1,3) == A(1,2) && A(1,3) ==a && A(1,1) == co)
        A(1,1)=b;
        elseif (A(2,3) == A(2,2) && A(2,3) ==a && A(2,1) == co)
        A(2,1)=b;
        elseif (A(3,3) == A(3,2) && A(3,3) ==a && A(3,1) == co)
        A(3,1)=b;
        
        elseif (A(1,1) == A(1,3) && A(1,1) == a && A(1,2) == co)
        A(1,2)=b;
        elseif (A(2,1) == A(2,3) && A(2,1) == a && A(2,2) == co)
        A(2,2)=b;
        elseif (A(3,1) == A(3,3) && A(3,1) == a && A(3,2) == co)
        A(3,2)=b;
        
        %coloane
        elseif (A(1,1) == A(2,1) && A(1,1) ==a && A(3,1) == co)
        A(3,1)=b;
        elseif (A(1,2) == A(2,2) && A(1,2) ==a && A(3,2) == co)
        A(3,2)=b;
        elseif (A(1,3) == A(2,3) && A(1,3) ==a && A(3,3) == co)
        A(3,3)=b;
        elseif (A(3,1) == A(2,1) && A(3,1) ==a && A(1,1) == co)
        A(1,1)=b;
        elseif (A(3,2) == A(2,2) && A(3,2) ==a && A(1,2) == co)
        A(1,2)=b;
        elseif (A(3,3) == A(2,3) && A(3,3) ==a && A(1,3) == co)
        A(1,3)=b;
        
        elseif (A(1,1) == A(3,1) && A(1,1) ==a && A(2,1) == co)
        A(2,1)=b;
        elseif (A(1,2) == A(3,2) && A(1,2) ==a && A(2,2) == co)
        A(2,2)==b;
        elseif (A(1,3) == A(3,3) && A(1,3) ==a && A(2,3) == co)
        A(2,3)=b;
        
        %diagonale
        elseif (A(1,1) == A(2,2) && A(1,1) == a && A(3,3) == co)
        A(3,3)=b;
        elseif (A(3,3) == A(2,2) && A(3,3) == a && A(1,1) == co)
        A(1,1)=b;
        elseif (A(1,3) == A(2,2) && A(1,3) == a && A(3,1) == co)
        A(3,1)=b;
        elseif (A(3,1) == A(2,2) && A(3,1) == a && A(1,3) == co)
        A(1,3)=b;
        
        elseif (A(1,1) == A(3,3) && A(1,1) == a && A(2,2) ==co)
        A(2,2)=b;
        elseif (A(1,3) == A(3,1) && A(1,3) == a && A(2,2) ==co)
        A(2,2)=b;
        
        %spec
        elseif (A(1,1) == A(3,3) && A(1,1) == a && A(2,1) ==co)
        A(2,1)=b;
        elseif (A(1,1) == A(3,3) && A(1,1) == a && A(2,3) ==co)
        A(2,3)=b;
        elseif (A(1,3) == A(3,1) && A(1,3) == a && A(2,1) ==co)
        A(2,1)=b;
        elseif (A(1,3) == A(3,1) && A(3,1) == a && A(2,3) ==co)
        A(2,3)=b;
        
        elseif strcmp(A(2,2),co)
          A(2,2)=b;
        elseif strcmp(A(1,1),co)
          A(1,1)=b;
        elseif strcmp(A(1,3),co)
          A(1,3)=b;
        elseif strcmp(A(3,1),co)
          A(3,1)=b;
        elseif strcmp(A(3,3),co)
          A(3,3)=b;
        elseif strcmp(A(1,2),co)
          A(1,2)=b;
        elseif strcmp(A(2,1),co)
          A(2,1)=b;
        elseif strcmp(A(2,3),co)
          A(2,3)=b;
        elseif strcmp(A(3,2),co)
          A(3,2)=b;
        endif
          
%Printarea tabelei dupa fiecare mutare utilizator-calculator.

   printf('      1     2    3\n');
   printf('    _________________\n');
   printf('   |     |     |     |\n');
   printf('1  |  %c  |  %c  |  %c  |\n',A(1,1),A(1,2),A(1,3));
   printf('   |_____|_____|_____|\n');
   printf('   |     |     |     |\n');
   printf('2  |  %c  |  %c  |  %c  |\n',A(2,1),A(2,2),A(2,3));
   printf('   |_____|_____|_____|\n');
   printf('   |     |     |     |\n');
   printf('3  |  %c  |  %c  |  %c  |\n',A(3,1),A(3,2),A(3,3));
   printf('   |_____|_____|_____|\n');
   printf('\n');
   
%Se verifica daca exista vre-un castigator.

    if (A(1,1) == A(1,2) && A(1,1) == A(1,3) && A(1,1) ~= co)
        won = A(1,1);
    elseif (A(2,1) == A(2,2) && A(2,1) == A(2,3) && A(2,1) ~= co)
        won = A(2,1);
    elseif (A(3,1) == A(3,2) && A(3,1) == A(3,3) && A(3,1) ~= co)
        won = A(3,1);
   
    elseif (A(1,1) == A(2,1) && A(1,1) == A(3,1) && A(3,1) ~= co) 
        won = A(1,1);
    elseif (A(1,2) == A(2,2) && A(1,2) == A(3,2) && A(1,2) ~= co) 
        won = A(1,2);
    elseif (A(1,3) == A(2,3) && A(1,3) == A(3,3) && A(1,3) ~= co) 
        won = A(1,3);
    
    elseif (A(1,1) == A(2,2) && A(1,1) == A(3,3) && A(1,1) ~= co)
        won = A(1,1);
    elseif (A(1,3) == A(2,2) && A(1,3) == A(3,1) && A(2,2) ~= co)
        won = A(1,3);
    
    elseif ~ismember(A, co)
        won = '2';
    else
        won = -1;
    endif

                
  endwhile
  
%Declararea rezultatului unei partide.
 
      if strcmp(won,'2');
    printf('REMIZA \n');
    elseif won == a
    printf('CASTIGATOR - %c\n',won);
    CONT(1)=CONT(1)+1;
    elseif won == b
    printf('CASTIGATOR - %c\n',won);
    CONT(2)=CONT(2)+1;
    endif
  
%Afisarea scorului general dupa fiecare partida, si interogarea de continuare sau sfrsit al jocului.
  
  printf('SCOR: JUCATOR-%d, BOT-%d\n',CONT(1),CONT(2));
  CON=input('Inca un joc?(n/y):','%c');
  
  endwhile  
          
          
endfunction
