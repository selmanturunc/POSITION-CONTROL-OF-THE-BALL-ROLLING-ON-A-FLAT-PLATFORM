load('data_fuzzy.mat')
plot(s1(:,1),s1(:,2),'k',s1(:,1),s1(:,3),'r')
legend('x','y')
xlabel('time(s)');
ylabel('position(cm)')
title('System Response')
grid on