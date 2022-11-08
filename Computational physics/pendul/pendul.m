%Pendul gravitational de amplitudine oarecare.
clear all; close all; clc;

g=9.8062;                 %m/s^2
l=1.44;
om2=g/l;

t0=0; tf=26;
N=15000;                    %Am marit cu mult valoare de puncte pentru a mari 
                            %precizia astefl incat timpul pentru a 10-a oscilatie sa fie exact.
t=linspace(t0,tf,N);
dt=t(2)-t(1);

theta=zeros(1,N);           %prealocare
tmax=zeros(1,10);

%conditii initiale
theta0=90/180*pi;            %rad
theta(1)=theta0;
theta(2)=theta0;             %viteza unghiulara este 0
j=1;
c=0.14115;                   %Acesta este "c" mult cautat.

for i=2:N-1
  theta(i+1)=2*theta(i)-theta(i-1)-c*dt*(theta(i)-theta(i-1))-dt^2*om2*sin(theta(i));
  if(theta(i+1) < theta(i)) && (theta(i) > theta(i-1))
    tmax(j)= t(i);
    j=j+1;
  end
  end
  
    disp(tmax(10));         %Timpul pentru a 10a osscilatie trebuie sa fie 25.078

figure(1);
plot(t,theta,'-b');
xlabel('t(s)');
ylabel('unghi rad');
grid;