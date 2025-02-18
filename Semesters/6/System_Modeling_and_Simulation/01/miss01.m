%% Zad1
x = -3:0.5:3;
y = [-0.25 -0.5 -0.75 -0.6 0.25 0 0.25 0.5 0.25 0 -0.25 -0.5 -0.25];

figure
hold on
plot(x,y, '*')
% plot(x,y, 'r')

%% Zad2
xp = 0.25;
yp = 0.4;
%1
y1 = interp1(x,y,xp, 'nearest');
blad1 = abs(y1-yp)
%2
y1 = interp1(x,y,xp, 'linear');
blad2 = abs(y1-yp)
%3
y1 = interp1(x,y,xp, 'spline');
blad3 = abs(y1-yp)
%4
y1 = interp1(x,y,xp, 'cubic');
blad4 = abs(y1-yp)

% zad2 - odp: cubic najdokladniejszy

% errorsy = [blad1, blad2, blad3, blad4];
% 
% errorsx = [yp, yp, yp, yp];
% plot(errorsx, errorsy)

%% zad3
xx = -3:0.01:3;
yy1 = interp1(x, y, xx,'nearest');
plot(xx, yy1, 'r')
yy1 = interp1(x, y, xx,'linear');
plot(xx, yy1, 'g')
yy1 = interp1(x, y, xx,'spline');
plot(xx, yy1, 'b')
yy1 = interp1(x, y, xx,'cubic');
plot(xx, yy1, 'y')

legend('Punkty', 'nearest', 'linear', 'spline', 'cubic')
% zad3 - odp: cubic

%% zad4
% 12 wykresow dla 13 stopnia wielomianu

for i=1:12
    subplot(3,4,i)
    p = polyfit(x, y, i);
    yy = polyval(p, xx);
    hold on 
    plot(x, y, 'k*', MarkerSize=5, LineWidth=1)
    plot(xx,yy)
    title(i)
end
% zad 4 - odp: 10

%% zad5

% zad 5 - odp: 
p = polyfit(x, y, 10);
yy = polyval(p, xp);
yp = 0.4;
xp = 0.25;
blad5 = abs(yy - yp)
% aproksymacja sobie poradzila gorzej, jest zblizony ale wiekszy