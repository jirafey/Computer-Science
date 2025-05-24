clc
close all 
clear all 


out = sim('wahadlosprezyna.slx');
r = out.r;
theta = out.theta;

l = str2double(get_param('wahadlosprezyna/Subsystem', 'l'));
m = str2double(get_param('wahadlosprezyna/Subsystem', 'm'));

for i=1:length(r)
    fi0 = theta(i)
    display(theta(i))
    fi1 =r(i)
    
  
    % okrag statyczny

    %hold on
    % okrag promieniu 5 umieszczony w punkcie 0, 0.
    [x,y] = generate_spring(l, fi1, fi0, 0,0);
    s = plot(x,y, 'b.','MarkerSize',0.3*m);
    %hold off
    % Ustawienia osi
    hold on
    mx = max(r) + l
    axis(mx, mx) % xlim, ylim
    xlim([-m-1 m+1]), ylim([-4.5*m 0])
    set(gca,'DataAspectRatio',[1 1 1])
    set(gca,'XTick',[-m-2 0 m+2],'YTick',[-m-2 0 m+2])
    hold off
    % narysowac linki
    %narysowac kulki
    % odpowiednio ustowic hol on hold off
    % axis 
    pause(0.01)
end