%Pendul graviational dublu.
clear all; close all; clc;


%Variatia condillor initiale. 
sizein=200;
omegain1 = linspace(2, 3, sizein);
omegain2 = linspace(2, 3, sizein);

for j = 1:sizein
    
    for k = 1:sizein
        
%Date de intrare.
g = 9.81;
m1 = 0.5; m2 = 0.25;
l1 = 0.6; l2 = 0.4;

%Conditi initiale.
theta10 = pi/3;
theta20 = 2*pi/3;
omega10 = omegain1(j);
omega20 = omegain2(k);

%Coeficenti pentru restrangerea sistemului.
r= l1/l2;
miu = m2/(m1+m2);

%Timpul.
t0 = 0;
tf = 10;
N = 1000;
t = linspace(t0, tf, N);
dt = t(2)-t(1);

%Preinitializare.
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
    
            % B1 = miu/dt^2*cos(theta2(i) - theta1(i));
            % A2 = B1/miu;
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
       
        %Coordonatele corpului m1.
        X1 = l1*sin(theta1(N));
       
        %Coordonatele corpului m2.
        X2 = X1+l2*sin(theta2(N));
       
        
        if (X2 < -0.8)
            red = 0;
            green = 1;
            blue = 0;
           
        elseif (-0.8 <= X2 < -0.6)
            red = 1;
            green = 1;
            blue = 0;
         elseif (-0.6 <= X2 < -0.4)
            red = 1;
            green = 0;
            blue = 0;
         elseif (-0.4 <= X2 < -0.2)
            red = 0;
            green = 0;
            blue = 1;
         elseif (-0.2 <= X2 < 0)
            red = 1;
            green = 1;
            blue = 1;
         elseif (0 <= X2 < 0.2)
            red = 1;
            green = 1;
            blue = 1;
         elseif (0.2 <= X2 < 0.4)
            red = 0;
            green = 0;
            blue = 1;
         elseif (0.4 <= X2 < 0.6)
            red = 1;
            green = 0;
            blue = 0;
          elseif (0.6 <= X2 < 0.8)
            red = 1;
            green = 1;
            blue = 0;
        else
            red = 0;
            green = 1;
            blue = 0;
        end;    
  
        plot(j, k,'.', 'color', [red green blue]);
        hold on;
    end;
end;
    
 
