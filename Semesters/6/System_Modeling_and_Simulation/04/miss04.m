clc
close all 
clear all 


out = sim('planeta.slx');
x = out.x;
y = out.y;
disp(length(y))
G = str2double(get_param('planeta/Subsystem', 'G'));
M = str2double(get_param('planeta/Subsystem', 'M'));
R = str2double(get_param('planeta/Subsystem', 'R'));
rs = str2double(get_param('planeta/Subsystem', 'rs'));

for i=1:length(y)
    fi0 =x(i)
    fi1 =y(i)
    
  
    % okrag statyczny

    rectangle('Position',[-R -R, 2*R, 2*R], 'Curvature', [1 1]);
    hold on
    % okrag promieniu 5 umieszczony w punkcie 0, 0.
    rectangle('Position',[-rs -rs, 2*rs, 2*rs], 'Curvature', [1 1]);

    s = plot(fi0, fi1, 'b.','MarkerSize',0.3*M);
    hold off
    % Ustawienia osi
    %axis([-1.1*M 1.1*M -1.1*M 1.1*M]) % xlim, ylim
    %set(gca,'DataAspectRatio',[1 1 1])
    %set(gca,'XTick',[-M 0 M],'YTick',[-M 0 M])
 
    % narysowac linki
    %narysowac kulki
    % odpowiednio ustowic hol on hold off
    % axis 
    pause(0.01)
end