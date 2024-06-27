namespace ConsoleApp4.lab0;
using ScottPlot;
public class kod
{
    static void Main(string[] args)
    {
        string cwd = "../../../images/figures";
        Directory.SetCurrentDirectory(cwd);
        int[] ints = new int[100];
        for (int i=0; i < ints.Length; i++)
        {
            ints[i] = i;
        }
        Draw.DrawPlot( ints, square(ints));
    }

    public static int[] square(int[] numbers)
    {
        int[] results = new int[numbers.Length];
        for (int i = 0; i < numbers.Length; i++)
        {
            results[i] += numbers[i] * numbers[i];
        }

        return results;
    }

    public static class Draw
    {
        public static void DrawPlot(int[] inputX, int[] inputY)
        {
            var plt = new Plot();
            plt.Title("Wykres dla lab0");
            plt.XLabel("integers");
            plt.YLabel("squared integers");
            plt.Add.Scatter(inputX, inputY);
            plt.SavePng("f.png", 1920, 1200);
        }
    }
}
