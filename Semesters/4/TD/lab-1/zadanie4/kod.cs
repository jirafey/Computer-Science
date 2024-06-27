using ScottPlot;

namespace ConsoleApp4.lab01.NewDirectory1;


public class kod
{
public static void Main(string[] args)
    {
        string cwd = "../../../images/figures";
        Directory.SetCurrentDirectory(cwd);

        const int n_pts_new = 22050;
        double[] t_new = new double[n_pts_new];
        double[] b5 = new double[n_pts_new];
        double[] b20 = new double[n_pts_new];
        double[] b50 = new double[n_pts_new];

        GenB(t_new, b5, b20, b50);

        DrawPlot(inputX:t_new, inputY:b5,title: "b1");
        DrawPlot(inputX:t_new, inputY:b20,title: "b2");
        DrawPlot(inputX:t_new, inputY:b50,title: "b3");
    }

    public static void GenB(double[] t, double[] b5, double[] b20, double[] b50)
    {
        const double sampling_frequency = 22050.0;
        const double pi = Math.PI;

        for (int i = 0; i < t.Length; i++)
        {
            double fi = (double)i;
            t[i] = fi / sampling_frequency;

            for (int h = 1; h <= 5; h++)
            {
                double fh = (double)h;
                b5[i] += Math.Pow(-1.0, fh) / fh * Math.Sin(fh * pi * 2 * t[i]);
            }
            for (int h = 1; h <= 20; h++)
            {
                double fh = (double)h;
                b20[i] += Math.Pow(-1.0, fh) / fh * Math.Sin(fh * pi * 2 * t[i]);
            }
            for (int h = 1; h <= 50; h++)
            {
                double fh = (double)h;
                b50[i] += Math.Pow(-1.0, fh) / fh * Math.Sin(fh * pi * 2 * t[i]);
            }

            b5[i] *= 2.0 / pi;
            b20[i] *= 2.0 / pi;
            b50[i] *= 2.0 / pi;
        }
    }

    public static void DrawPlot(double[] inputX, double[] inputY, string title)
    {
        var plt = new Plot();
        plt.Title(text:$"Wykres dla {title}");
        plt.XLabel("Time (s)");
        plt.YLabel("Amplitude");
        plt.Add.Scatter(xs:inputX, ys:inputY);
        plt.SavePng(filePath:$"{title}.png",width: 1920,  height:1200);
    }
}


