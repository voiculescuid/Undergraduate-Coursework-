%Pendul graviational dublu
clear all; close all; clc;

th1=linspace(0,pi,100);
th2=linspace(0,pi,100);
figure(1);
hold on;

for i1=1:100

  for j1=1:100
%data de intrare
g = 9.81;
m1 = 0.5; m2 = 0.25;
l1 = 0.6; l2 = 0.4;
%conditi initiale
theta10 = th1(i1);
theta20 = th2(j1);
omega10 = 0;
omega20 = 0;
%coeficenti pentru restrangerea sistemului
r= l1/l2;
miu = m2/(m1+m2);
%timpul
t0 = 0;
tf = 10;
N = 100;
t = linspace(t0, tf, N);
dt = t(2)-t(1);
%initializa pentru 
theta1 = zeros(1,N);
theta2 = zeros(1,N);
theta1(1) = theta10;
theta2(1) = theta20;
theta1(2) = theta10+dt*omega10;
theta2(2) = theta20+dt*omega20;

A1 = r/dt^2;
B2 = 1/r/dt^2;


for i = 2:N-1
    
    s = sin(theta2(i)-theta1(i));
    c = cos(theta2(i)-theta1(i));
    
    %B1 = miu/dt^2*cos(theta2(i) - theta1(i));
    %A2 = B1/miu;
    A2 = c/dt^2;
    B1 = miu*A2;
    
    M1 = miu*(theta2(i)-theta2(i-1))^2*s/dt^2 - g/l2*sin(theta1(i)) - r/dt^2*theta1(i-1) + 2*r/dt^2*theta1(i) - miu/dt^2*theta2(i-1)*c + 2*miu/dt^2*theta2(i)*c;
    M2 = -(theta1(i)-theta1(i-1))^2/dt^2*s - g/l1*sin(theta2(i)) - 1/r/dt^2*theta2(i-1) + 2/r/dt^2*theta2(i)- theta1(i-1)/dt^2* c + 2*theta1(i)/dt^2*c;
        
    delta = A1*B2-A2*B1;
    delta1 = M1*B2-M2*B1;
    delta2 = A1*M2-A2*M1;
  
    theta1(i+1) = delta1/delta;
    theta2(i+1) = delta2/delta;
    
end;

Nx = 800;
Ny = 600;
Ox = round(Nx/2);
Oy = Ny;

%coordonatele corpului m1
X1 = Ox+l1*sin(theta1);
Y1 = Oy-l1*cos(theta1);

%coordonatele corpului m2
X2 = X1+l2*sin(theta2);
Y2 = Y1-l2*cos(theta2);

plot(theta10,theta20,'-r');hold on;

  end
  
end