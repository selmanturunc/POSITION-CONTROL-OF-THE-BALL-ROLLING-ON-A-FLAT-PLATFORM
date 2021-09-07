A=0.06;
B=0.06;
C=0.031;
h=0.06;
b=0.09;
theta=-30;
syms  fi alfa
s=zeros(1,61);
mn=zeros(1,61);
ss=zeros(1,61);
for i=1:61 
eqn1=-C*sind(theta)+B*cosd(fi)==h-A*sind(alfa);
eqn2=-C*cosd(theta)-B*sind(fi)==-b+A*cosd(alfa);
[L]=solve([eqn1,eqn2],[fi,alfa]);

q=double(L.alfa);
s(i)=q(1);
ss(i)=q(2);
mn(i)=theta;
theta=theta+1;
end
plot(s,mn,'k','LineWidth',1.2);
hold on
plot(C/A*mn,mn,'r.')
grid on
title('Geometrical Analysis');
xlabel('Angle \alpha [°]');
ylabel('Angle \theta [°]');
legend('geometrical realationship','linearized relationship');



