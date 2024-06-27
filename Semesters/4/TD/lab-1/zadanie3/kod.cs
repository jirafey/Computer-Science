using ScottPlot;

namespace ConsoleApp4.lab01.NewDirectory1;


public class kod
{
    public static void Main(string[] args)
    {
        string cwd = "../../../images/figures";
        Directory.SetCurrentDirectory(cwd);

        const int n_pts = 8000;
        double[] t = new double[n_pts];
        double[] u = new double[n_pts];
        GenU(t, u);
        DrawPlot(t, u, "u");
    }

    public static void GenU(double[] t, double[] u)
    {
        const double sampling_frequency = 8000.0;
        const double pi = Math.PI;

        for (int i = 0; i < t.Length; i++)
        {
            double fi = (double)i;
            t[i] = fi / sampling_frequency;

            if (t[i] < 0.1)
            {
                u[i] = Math.Sin(6 * pi * t[i]) * Math.Cos(5 * pi * t[i]);
            }
            else if (t[i] < 0.4)
            {
                u[i] = -1.1 * t[i] * Math.Cos(41 * pi * Math.Pow(t[i], 2));
            }
            else if (t[i] < 0.72)
            {
                u[i] = t[i] * Math.Sin(20 * Math.Pow(t[i], 4));
            }
            else if (t[i] < 1)
            {
                u[i] = 3.3 * (t[i] - 0.72) * Math.Cos(27 * t[i] + 1.3);
            }
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


