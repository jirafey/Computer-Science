// 1
const std = @import("std");
const print = std.debug.print;

const math = std.math;

pub const zzplot = @import("zzplot_import_name");
pub const nvg = zzplot.nanovg;

pub const Figure = zzplot.Figure;
pub const Axes = zzplot.Axes;
pub const Plot = zzplot.Plot;
pub const Color = zzplot.Color;

pub const minMax = zzplot.minMax;

const c = @cImport({
    @cInclude("glad/glad.h");
    @cInclude("GLFW/glfw3.h");
});

pub fn genSine(t: []f32, b5: []f32, b20: []f32, b50: []f32) !void {
    const sampling_frequency: f32 = 22050;
    const n_pts = t.len;
    for (0..n_pts) |i| {
        t[i] = @as(f32, @floatFromInt(i)) / sampling_frequency;
        std.debug.print("{d}\n", .{t[i]});
        const two: f32 = 2.0;
        for (1..5) |h| {
            const fh: f32 = @floatFromInt(h);
            b5[i] += (math.pow(f32, -1.0, fh)) / fh * math.sin(fh * math.pi * 2 * t[i]);
        }
        for (1..20) |h| {
            const fh: f32 = @floatFromInt(h);
            b20[i] += (math.pow(f32, -1.0, fh)) / fh * math.sin(fh * math.pi * 2 * t[i]);
        }
        for (1..50) |h| {
            const fh: f32 = @floatFromInt(h);
            b50[i] += (math.pow(f32, -1.0, fh)) / fh * math.sin(fh * math.pi * 2 * t[i]);
        }
        b5[i] = b5[i] * (two / math.pi);
        b20[i] = b20[i] * (two / math.pi);
        b50[i] = b50[i] * (two / math.pi);
        std.debug.print("{d}\n", .{t[i]});
    }
}

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    const shared = try zzplot.createShared();

    // generate data for plotting
    const n_pts = 22050;
    const t: []f32 = try allocator.alloc(f32, n_pts);
    const b5: []f32 = try allocator.alloc(f32, n_pts);
    const b20: []f32 = try allocator.alloc(f32, n_pts);
    const b50: []f32 = try allocator.alloc(f32, n_pts);
    try genSine(t, b5, b20, b50);

    // nvg context creation goes after gladLoadGL
    const vg = try nvg.gl.init(allocator, .{
        .debug = true,
    });

    zzplot.Font.init(vg);
    // defer vg.deinit();  // DO NOT UNCOMMENT THIS LINE, WILL GIVE ERROR UPON EXIT

    const fig5 = try Figure.init(allocator, shared, vg, .{
        .title_str = "Tabela 1",
        .disp_fps = true,
    });

    const ax5 = try Axes.init(fig5, .{
        .title_str = "b(1)(t)",
        .xlabel_str = "time",
        .ylabel_str = "b(1)(t)",
    });

    const fig20 = try Figure.init(allocator, shared, vg, .{
        .title_str = "Tabela 1",
        .disp_fps = true,
    });

    const ax20 = try Axes.init(fig20, .{
        .title_str = "b(2)(t)",
        .xlabel_str = "time",
        .ylabel_str = "b(2)(t)",
    });

    const fig50 = try Figure.init(allocator, shared, vg, .{
        .title_str = "Tabela 1",
        .disp_fps = true,
    });

    const ax50 = try Axes.init(fig50, .{
        .title_str = "b(3)(t)",
        .xlabel_str = "time",
        .ylabel_str = "b(3)(t)",
    });

    const plt5 = try Plot.init(ax5, .{});
    const plt20 = try Plot.init(ax20, .{});
    const plt50 = try Plot.init(ax50, .{});

    ax5.set_limits(.{ 0, 1 }, .{ -1, 1 }, .{});
    ax20.set_limits(.{ 0, 1 }, .{ -1, 1 }, .{});
    ax50.set_limits(.{ 0, 1 }, .{ -1, 1 }, .{});

    while ((fig5.live or fig20.live or fig50.live)) {
        fig5.begin();

        ax5.draw();
        plt5.plot(t, b5);

        ax5.text(2, -5, .{
            .str = "",
            .alignment = .{ .horizontal = .left, .vertical = .middle },
        });

        fig5.end();

        fig20.begin();

        ax20.draw();
        plt20.plot(t, b20);

        ax20.text(2, -5, .{
            .str = "",
            .alignment = .{ .horizontal = .left, .vertical = .middle },
        });

        fig20.end();

        fig50.begin();

        ax50.draw();
        plt50.plot(t, b50);

        ax50.text(2, -5, .{
            .str = "",
            .alignment = .{ .horizontal = .left, .vertical = .middle },
        });

        fig50.end();
    }

    c.glfwTerminate();
}
