load('Datas.mat')
plot(t1,x1,'k')
legend('x')
xlabel('time(s)');
ylabel('position(cm)')
title('System Response')
grid on
figure
plot(s2(:,1),s2(:,2),'k',s2(:,1),s2(:,3),'r')
legend('x','y')
xlabel('time(s)');
ylabel('position(cm)')
title('System Response')
grid on
figure
plot(s3(:,1),s3(:,2),'k',s3(:,1),s3(:,3),'r')
legend('x','y')
xlabel('time(s)');
ylabel('position(cm)')
title('System Response')
grid on
