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
        double[] x = new double[n_pts];
        double[] y = new double[n_pts];
        double[] z = new double[n_pts];
        double[] v = new double[n_pts];
        GenX(t,x);
        GenYZV(t, x, y, z, v);

        DrawPlot(inputX: t, inputY: y, title: "y");
        DrawPlot(inputX: t, inputY: z, title: "z");
        DrawPlot(inputX: t, inputY: v, title: "v");

    }

    public static void GenX(double[] t, double[] x)
    {
        const double signal_frequency = 1.0;
        const double sampling_frequency = 8000.0;
        const int sigma = 3;

        for (int i = 0; i < t.Length; i++)
        {
            double fi = (double)i;
            t[i] = fi / sampling_frequency;
            x[i] = Math.Cos(2 * Math.PI * signal_frequency * t[i] + sigma) * Math.Cos(2.5 * Math.Pow(t[i], 0.2) * Math.PI);
        }
    }
    public static void GenYZV(double[] t, double[] x, double[] y, double[] z, double[] v)
    {
        const double signal_frequency = 1.0;
        const double sampling_frequency = 8000.0;
        const int sigma = 3;

        for (int i = 0; i < t.Length; i++)
        {
            double fi = (double)i;
            t[i] = fi / sampling_frequency;
            y[i] = t[i] * x[i] / (3 + Math.Cos(20 * Math.PI * t[i]));
            z[i] = Math.Pow(t[i], 2) * Math.Abs(x[i] * y[i] - 2 / (10 + y[i]));
            v[i] = Math.Pow(z[i], 3) + 3 * Math.Sin(z[i] * y[i]) * Math.Abs(y[i] - x[i]);
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


