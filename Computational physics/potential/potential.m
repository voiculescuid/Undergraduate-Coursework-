%Potential.m
clear all; close all; clc;

Q=1e-6;
l=0.1;
ke=9*1e+9;
N=250;

x=linspace(0,l,N);
y=x; z=x;

dmin=25*l/N;
 
xp=0; yp=0; zp=-dmin;
for i1=1:11
    xp=0;
    
    for i2=1:11      
    sigma=0;
    
    %tic;

        for i=1:N
            for j=1:N
                for k=1:N
                    f=((xp-x(i))^2+(yp-y(j))^2+(zp-z(k))^2)^(-0.5);
                    sigma = sigma + f;
                end
            end
        end

    %toc;
    
        V(i1,i2)=ke*Q/N^3*sigma;
        xp=xp+dmin;
        
    end
    
    yp=yp+dmin;
    
end

surf(V);