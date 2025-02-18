clc
close all 
clear all 


out = sim('maszyna_atwooda.slx');
x = out.x;
y = out.y;
r = out.r;

r0 = str2double(get_param('maszyna_atwooda/Subsystem', 'r0'));
m1 = str2double(get_param('maszyna_atwooda/Subsystem', 'm1'));
m2 = str2double(get_param('maszyna_atwooda/Subsystem', 'm2'));
M = str2double(get_param('maszyna_atwooda/Subsystem', 'M'));
theta0 = str2double(get_param('maszyna_atwooda/Subsystem', 'theta0'));

for i=1:length(x)
    xx = x(i)
    yy = y(i)
    rr = r(i)
    
    hold on
    punkt = plot(xx,yy, 'b.','MarkerSize',10);
    linka = plot([0,xx],[0,yy], 'r.','MarkerSize',5);

    linka2 = plot([-10,0],[0,yy], 'r.','MarkerSize',5);
    punkt2 = plot(xx-10,yy, 'b.','MarkerSize',10);
    %-10 r0-r
    hold off
    % Ustawienia osi
    hold on
    %mx = max(r) + r0
    %axis(mx, mx) % xlim, ylim
    %xlim([-m1-1 m1+1]), ylim([-4.5*m1 0])
    %set(gca,'DataAspectRatio',[1 1 1])
    %set(gca,'XTick',[-m1-2 0 m1+2],'YTick',[-m1-2 0 m1+2])
    hold off
    % narysowac linki
    %narysowac kulki
    % odpowiednio ustowic hol on hold off
    % axis 
    pause(0.01)
end