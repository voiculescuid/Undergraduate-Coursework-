function m = morse ()

h = {'H' {} {}};
v = {'V' {} {}};
f = {'F' {} {}};
l = {'L' {} {}};
p = {'P' {} {}};
j = {'J' {} {}};
b = {'B' {} {}};
x = {'X' {} {}};
c = {'C' {} {}};
y = {'Y' {} {}};
z = {'Z' {} {}};
q = {'Q' {} {}};

s = {'S' h v};
u = {'U' f {}};
r = {'R' l {}};
w = {'W' p j};
d = {'D' b x};
k = {'K' c y};
g = {'G' z q};
o = {'O' {} {}};

i = {'I' s u};
a = {'A' r w};
n = {'N' d k};
M = {'M' g o};

e = {'E' i a};
t = {'T' n M};

m = {'' e t};

%Generarea cell array pentru cod morse.

endfunction
