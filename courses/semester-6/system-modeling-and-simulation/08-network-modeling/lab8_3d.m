clc;
close all; 
clear all;

out = sim("lab08_3d.slx");
x_coords = out.x;
y_coords = out.y;

mass = str2double(get_param('lab08_3d/Subsystem','m'));
rod_len = str2double(get_param('lab08_3d/Subsystem','L'));
static_pt_x = str2double(get_param('lab08_3d/Subsystem','xi'));
static_pt_y = str2double(get_param('lab08_3d/Subsystem','yi'));
static_pt_attr = str2double(get_param('lab08_3d/Subsystem','ai')); % Attribute for static points
static_pt_z = str2double(get_param('lab08_3d/Subsystem','di')); % Z for static points

figure;
axis_limits = [-rod_len*1.1, rod_len*1.1, -rod_len*1.1, rod_len*1.1, -0.2, rod_len+0.2];

for k = 1:length(x_coords)
    cla;
    hold on;

    plot3(static_pt_x(static_pt_attr > 0.001), ...
          static_pt_y(static_pt_attr > 0.001), ...
          static_pt_z(static_pt_attr > 0.001), ...
          'g^', 'MarkerSize', 12);

    plot3(static_pt_x(static_pt_attr < -0.001), ...
          static_pt_y(static_pt_attr < -0.001), ...
          static_pt_z(static_pt_attr < -0.001), ...
          'mv', 'MarkerSize', 12);

    current_x = x_coords(k);
    current_y = y_coords(k);
    
    horizontal_dist_sq = current_x^2 + current_y^2;
    
    if rod_len^2 >= horizontal_dist_sq
        vertical_dist_from_pivot = sqrt(rod_len^2 - horizontal_dist_sq);
    else
        vertical_dist_from_pivot = 0;
    end
    
    current_z = rod_len - vertical_dist_from_pivot;

    plot3(current_x, current_y, current_z, ...
          'yo', 'MarkerSize', 7 + mass * 5, 'MarkerFaceColor', 'y');

    line([0, current_x], [0, current_y], [rod_len, current_z], ...
         'Color', 'c', 'LineStyle', ':', 'LineWidth', 2.5);
    hold off;
    axis(axis_limits);
    grid on;
    view(35, 30);
    pause(0.022);
end
