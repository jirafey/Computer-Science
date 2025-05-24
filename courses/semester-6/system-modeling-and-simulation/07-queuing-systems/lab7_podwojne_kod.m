model_name = "lab7_podwojne";
out = sim(model_name);
[fi1, fi2] = deal(out.fi1, out.fi2);
sub = "/Subsystem";

path = model_name + sub;

[l1, l2, m1, m2] = deal(...
    str2double(get_param(path,'l1')), ...
    str2double(get_param(path,'l2')), ...
    str2double(get_param(path,'m1')), ...
    str2double(get_param(path,'m2')));

for i=1:size(fi1, 1)
    
    [a, c] = deal(-l1 * sin(fi1(i)), -l1 * cos(fi1(i)));

    
    [b, d] = deal(-l2 * sin(fi2(i)) + a, -l2 * cos(fi2(i)) + c);

    
    [ax_1, ax_2, ax_3, ax_4] = deal(...
        -0.7*(l1 + l2), 0.8*(l1 + l2), ...
        -1.07*(l1 + l2), 1.07*(l1 + l2));

    plot([0 a], [0 c], 'LineWidth',13);
    hold on;

    plot(a, c, 'r.','MarkerSize', 26*m1);
    plot([a b],[c d],'LineWidth',13);
    plot(b, d, 'k.','MarkerSize', 26*m2);
    hold off;

    axis([ax_1 ax_2 ax_3 ax_4]);
    stop_time = 2^-5;
    pause(stop_time);
end