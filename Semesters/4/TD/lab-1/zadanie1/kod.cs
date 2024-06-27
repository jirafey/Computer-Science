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
        GenX(t,x);

        DrawPlot(inputX: t, inputY: x, title: "x");
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


