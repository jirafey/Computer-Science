using System.Diagnostics;
using System.Numerics;
using MathNet.Numerics.IntegralTransforms;
using ScottPlot;

internal class kod
{
    public static void Main(string[] args)
    {
        string cwd = "../../../images/figures";
        Directory.SetCurrentDirectory(cwd);

        double fs = 8000;
        double f = fs/2;
        double t = 1;
        double fi = 1;
        int n = System.Convert.ToInt32(fs * t);
        
        // DAT.DAT_DFT(kod.FT.fn.toDrawX, n, fs, f, fi, "x");
        // DAT.DAT_DFT(kod.FT.fn.toDrawY, n, fs, f, fi, "y");
        // DAT.DAT_DFT(kod.FT.fn.toDrawZ, n, fs, f, fi, "z");
        // DAT.DAT_DFT(kod.FT.fn.toDrawV, n, fs, f, fi, "v");
        //
        // DAT.DAT_U_DFT(f, fs, "u");
        // DAT.DAT_B_DFT(f, fs, 5, "b1");
        // DAT.DAT_B_DFT(f, fs, 20, "b2");
        // DAT.DAT_B_DFT(f, fs, 50, "b3");

        DAT.DAT_FFT(kod.FT.fn.toDrawX, n, fs, f, fi, "x");
        DAT.DAT_FFT(kod.FT.fn.toDrawY, n, fs, f, fi, "y");
        DAT.DAT_FFT(kod.FT.fn.toDrawZ, n, fs, f, fi, "z");
        DAT.DAT_FFT(kod.FT.fn.toDrawV, n, fs, f, fi, "v");

        DAT.DAT_U_FFT(f, fs, "u");
        DAT.DAT_B_FFT(f, fs, 5, "b1");
        DAT.DAT_B_FFT(f, fs, 20, "b2");
        DAT.DAT_B_FFT(f, fs, 50, "b3");
    }

    public static class FT
    {

        public static double[] FK(double fs, int N)
        {
            double[] f = new double[N];
            for (int k = 0; k < N; k++)
            {
                f[k] = k * fs / N;
            }
            return f;
        }
    
        public static double[] DB(double[] input)
        {
            double[] output = new double[input.Length];

            for (int k = 0; k < input.Length; k++)
            {
                output[k] = 10 * Math.Log10(input[k]); 
            }

            return output;
        }
        public static double[,] DFT(double[] samples)
        {
            int N = samples.Length;
            double[,] output = new double[2, N];

            for (int k = 0; k < N; k++)
            {
                double realSum = 0.0;
                double imagSum = 0.0;

                for (int n = 0; n < N; n++)
                {
                    double angle = (2 * Math.PI * k * n) / N;
                    realSum += samples[n] * Math.Cos(angle);
                    imagSum += samples[n] * Math.Sin(angle);
                }

                output[0, k] = realSum;
                output[1, k] = imagSum;
            }

            return output;
        }
        public static double[,] FFT(double[] input)
        {
            double[,] output = new double[2, input.Length];
            Complex[] complexInput = new Complex[input.Length];

            for (int i = 0; i < input.Length; i++)
            {
                complexInput[i] = new Complex(input[i], 0);
            }

            Fourier.Forward(complexInput, FourierOptions.Matlab);

            for (int i = 0; i < input.Length; i++)
            {
                output[0, i] = complexInput[i].Real;
                output[1, i] = complexInput[i].Imaginary;
            }

            return output;

        }

        public static class fn
        {

            // List 1 (1.)
            public static double X(double f, double t, double fi)
            {
                double x = (Math.Cos(2 * Math.PI * f * fi) * Math.Cos(2.5 * Math.Pow(t, 0.2) * Math.PI));
                return x;
            }
            // List 2 (1.)
            public static double Y(double f, double t, double fi)
            {

                double y = (X(f, t, fi) * t)/ 3 + Math.Cos(20* Math.PI * t);
                return y;

            }
            public static double Z(double f, double t, double fi)
            {
                double z = Math.Pow(t, 2) * Math.Abs(X(f,t,fi) * Y(f,t,fi) - 2/(10 + Y(f,t,fi)));
                return z;
            }
            public static double V(double f, double t, double fi)
            {
                double v = Math.Pow(Z(f, t, fi), 3) +
                           3 * Math.Sin(Z(f, t, fi) * Y(f, t, fi)) * Math.Abs(Y(f, t, fi) - X(f, t, fi));
                return v;
            }
                
            // List 3 (1.)
            public static double U(double t)
            {
                double[] range = { 0, 0.1, 0.4, 0.72, 1 };
                double u = 0.0;
                if (t >= range[0] && t < range[1])
                {
                    u = Math.Sin(6 * Math.PI * t) * Math.Cos(5* Math.PI * t);
                    return u;
                }
                if (t >= range[1] && t < range[2])
                {
                    u = -1.1 * t * Math.Cos(41 * Math.PI * Math.Pow(t,2));
                    return u;
                }
                if (t >= range[2] && t < range[3])
                {
                    u = t * Math.Sin(20 * Math.Pow(t, 4));
                    return u;

                }
                if (t >= range[3] && t < range[4])
                {
                    u = 3.3 * (t - 0.72) * Math.Cos(27 * t + 1.3);
                    return u;
                }

                return u;
            }
            
            // List 4 (1.)
            public static double[] B(int H, double t)
            {
                double[] b = new double[H];
                for (int h = 0; h < H; h++)
                {
                    b[h] +=  Math.Sin((Math.Sin(Math.PI * h / 7 * t) * Math.PI * t * h)) / (2 * Math.Pow(h, 2) + 1);
                }

                return b;
            }
                
            public static double[] toDrawX(int n,double fs, double f, double fi)
            {
                double t = 0;
                double[] x = new double[n];
                
                for (int i = 0; i < n; i++)
                {
                    t = i / fs;
                    x[i] = kod.FT.fn.X(f, t, fi);
                }
                return x;
            }
            public static double[] toDrawY(int n,double fs, double f, double fi)
            {
                
                double[] y = new double[n];

                for (int i = 0; i < n; i++)
                { 
                    double t = i / fs;
                    y[i] = kod.FT.fn.Y(f, t, fi);

                }

                return y;

            }
            public static double[] toDrawZ(int n,double fs, double f, double fi)
            {
                
                double[] z = new double[n];

                for (int i = 0; i < n; i++)
                { 
                    double t = i / fs;
                    z[i] = kod.FT.fn.V(f, t, fi);

                }

                return z;

            }
            public static double[] toDrawV(int n,double fs, double f, double fi)
            {
                
                double[] v = new double[n];

                for (int i = 0; i < n; i++)
                { 
                    double t = i / fs;
                    v[i] = kod.FT.fn.Z(f, t, fi);

                }

                return v;

            }
            public static double[] toDrawU(double f)
            {
                
                double[] u = new double[90];
              
                int n1 = 0;
                for (double i = 0.1; i < 1; i+=0.01)
                {
                    u[n1] = kod.FT.fn.U(i);
                    n1++;
                }

                return u;

            }
            public static double[] toDrawB(int N,double f)
            {
                
                double[] b = new double[N];
                double t = f * 1;

                b = kod.FT.fn.B(N, t);

                return b;
            }

        }

    }
    public static class DAT
    {
        public static void DAT_DFT(Func<int, double, double, double, double[]> signalFunc, int n, double fs, double f, double fi, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(signalFunc(n, fs, f, fi), fs, $"{filenamePrefix}.png", FT.DFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"DFT {time}");
            timer.Reset();
        }
        

        public static void DAT_U_DFT(double f, double fs, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(kod.FT.fn.toDrawU(f), fs, $"{filenamePrefix}.png", FT.DFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"DFT for {filenamePrefix}: {time}");
            timer.Reset();
        }

        public static void DAT_B_DFT(double f, double fs, int b, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(kod.FT.fn.toDrawB(b, f), fs, $"{filenamePrefix}.png", FT.DFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"DFT for {filenamePrefix} (B({b})): {time}");
            timer.Reset();
        }

        public static void DAT_FFT(Func<int, double, double, double, double[]> signalFunc, int n, double fs, double f, double fi, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(signalFunc(n, fs, f, fi), fs, $"{filenamePrefix}.png", FT.FFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"FFT {time}");
            timer.Reset();
        }
        public static void DAT_U_FFT(double f, double fs, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(kod.FT.fn.toDrawU(f), fs, $"{filenamePrefix}.png", FT.FFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"FFT for {filenamePrefix}: {time}");
            timer.Reset();
        }

        public static void DAT_B_FFT(double f, double fs, int b, string filenamePrefix)
        {
            Stopwatch timer = new Stopwatch();
            TimeSpan time;

            timer.Start();
            Draw.DrawPlot(kod.FT.fn.toDrawB(b, f), fs, $"{filenamePrefix}.png", FT.FFT);
            timer.Stop();
            time = timer.Elapsed;
            Console.WriteLine($"FFT for {filenamePrefix} (B({b})): {time}");
            timer.Reset();
        }
    }
    public static class Draw
    {

        public static void DrawPlot(double[] input, double fs, string name, Func<double[], double[,]> transformFunction)
        {
            double[,] output = transformFunction(input);

            double[] ft = new double[output.GetLength(1)];
            for (int k = 0; k < output.GetLength(1); k++)
            {
                ft[k] = Math.Sqrt(Math.Pow(output[0, k], 2) + Math.Pow(output[1, k], 2));
            }

            double[] FK = FT.FK(fs, ft.Length);

            double[] ftHalf = new double[ft.Length / 2];
            double[] FKHalf = new double[FK.Length / 2];

            for (int i = 0; i < ft.Length / 2; i++)
            {
                ftHalf[i] = ft[i];
                FKHalf[i] = FK[i];
            }

            Plot plt = new Plot();
            plt.Add.Scatter(FKHalf, ftHalf);
            plt.XLabel("Frequency");
            plt.YLabel("Amplitude spectrum");
            plt.Title($"Spectrum FFT");
            plt.SavePng($"{name}", 1920, 1080);
        }
    }

}
