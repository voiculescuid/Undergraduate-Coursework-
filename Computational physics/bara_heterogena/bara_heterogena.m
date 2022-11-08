%Difuzia calduri intr-un mediu 1D heterogen.
clear all; close all; clc;

%Date initiale.
l1 = 0.2;
l2 = 0.05;
lambda1 = 210; 
lambda2 = 46;
ro1 = 2700;
ro2 = 7800;
c1 = 900;
c2 = 490;
D1 = lambda1/ro1/c1;
D2 = lambda2/ro2/c2;
T10 = 800;
T20 = 100;
Nt = 2000;          %Discretizare temporala.
Nx = 50;
t0 = 0;
tf = 200;
xs =-l1;
xd = l2;
t = linspace(t0, tf, Nt);
dt = t(2) - t(1);
x = linspace(xs, xd, Nx);
dx = x(2) - x(1);
T0 = T10*ones(1, Nx);
T0(x > 0) = T20;
D = D1*ones(1,Nx);
D(x > 0) = D2;
T = T0;


%COLORMAP
colormap(jet);
newrange = [1:64/800:64]'; 
oldrange = [1:1:64]';
colormapinterp = interp1(oldrange,colormap,newrange); 
temprange = [100:1:800];

%BARA
yy=linspace(1.15,1.35,200);
xx=ones(200);

c = colorbar;
c.Location = 'southoutside';
c.Ticks = [100, 200, 300, 400, 500, 600, 700, 800];
c.Label.String = 'Temperatura {\circ}C';
caxis( [100 800] );


Film = moviein(Nx); figure(1); hold on;
for i = 2:Nt
    Tant = T;
    
    for j = 2:Nx-1
        T(j) = Tant(j) + dt/dx^2*D(j)*(Tant(j-1) + Tant(j+1) -2*Tant(j));
    end
    
    %Capete termostate.
    T(1) = T10;
    T(Nx) = T20;
    
    %Capete izolate.
    %T(1) = T(2);
    %T(Nx) = T(Nx-1);
    
    x2=xx;
    for count=1:Nx
        x2=xx*0.005 + x2;
        axis([0.75 1.5 1 1.5]);
        k = find(temprange==round(T(count)));
        color= colormapinterp(k,:,:); 
        
        plot(x2, yy,'.', 'color', color);
    end

    Film(i-1, :) = getframe;
end

hold off;

figure(2);
movie(Film, 1, round(Nt/tf));
