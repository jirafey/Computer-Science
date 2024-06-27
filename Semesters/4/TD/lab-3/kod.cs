using ScottPlot;
using System.Numerics;
using MathNet.Numerics.IntegralTransforms;

namespace lab3
{
    public class kod
    {
        public static void Main(string[] args)
        {
            int fs = 8000;
            int n = 8000;
            double fm = 120;
            double fn = 1000;
            double[] frequencies = CalculateFrequencies(n, fs);
            string cwd = "../../../images/figures";
            Directory.SetCurrentDirectory(cwd);
            
            // 2.1.1, 3.1.1
            // a) 1 > ka > 0
            double ka = 0.99;
            draw.DrawPlot(toDraw(fm, fn, ka, n, fs, zA), fs, "za_a.png", FT.FFT);
            
            double[] za = toDraw(fm, fn, ka, n, fs, zA);
            double[,] zaFFT = FT.FFT(za);
            double[] zaMagnitude = Magnitude(zaFFT);
            double[] zaDecibel = FT.DB(zaMagnitude);
            draw.DrawPlotLog10(zaDecibel, fs, "za_a_widmo.png", FT.FFT);
            
            // b) 12 > ka > 2
            ka = 11.99;
            draw.DrawPlot(toDraw(fm, fn, ka, n, fs, zA), fs, "za_b.png", FT.FFT);
            za = toDraw(fm, fn, ka, n, fs, zA);
            zaFFT = FT.FFT(za);
            zaMagnitude = Magnitude(zaFFT);
            zaDecibel = FT.DB(zaMagnitude);
            draw.DrawPlotLog10(zaDecibel, fs, "za_b_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 12)} Hz");
            
            // c) ka > 20
            ka = 21 * Math.PI;
            draw.DrawPlot(toDraw(fm, fn, ka, n, fs, zA), fs, "za_c.png", FT.FFT);
            za = toDraw(fm, fn, ka, n, fs, zA);
            zaFFT = FT.FFT(za);
            zaMagnitude = Magnitude(zaFFT);
            zaDecibel = FT.DB(zaMagnitude);
            draw.DrawPlotLog10(zaDecibel, fs, "za_c_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, ka, n, fs, zA), frequencies, 12)} Hz");
            
            
            // 2.1.2
            // a) kp < 1
            double kp = 0.99;
            double[] zp = toDraw(fm, fn, ka, n, fs, zP);
            draw.DrawPlot(toDraw(fm, fn, kp, n, fs, zP), fs, "zp_a.png", FT.FFT);
            
            double[,] zpFFT = FT.FFT(zp);
            double[] zpMagnitude = Magnitude(zpFFT);
            double[] zpDecibel = FT.DB(zpMagnitude);
            draw.DrawPlotLog10(toDraw(fm, fn, kp, n, fs, zP), fs, "zp_a_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 12)} Hz");
            
            // b) pi > kp > 0
            kp = Math.PI -0.01;
            draw.DrawPlot(toDraw(fm, fn, kp, n, fs, zP), fs, "zp_b.png", FT.FFT);
            
            zp = toDraw(fm, fn, ka, n, fs, zP);
            zpFFT = FT.FFT(zp);
            zpMagnitude = Magnitude(zpFFT);
            zpDecibel = FT.DB(zpMagnitude);
            draw.DrawPlotLog10(zpDecibel, fs, "zp_b_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 12)} Hz");
            
            // c) kp > 2pi
            kp = 120 * Math.PI;
            draw.DrawPlot(toDraw(fm, fn, kp, n, fs, zP), fs, "zp_c.png", FT.FFT);
            
            zp = toDraw(fm, fn, ka, n, fs, zP);
            zpFFT = FT.FFT(zp);
            zpMagnitude = Magnitude(zpFFT);
            zpDecibel = FT.DB(zpMagnitude);
            draw.DrawPlotLog10(zpDecibel, fs, "zp_c_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kp, n, fs, zP), frequencies, 12)} Hz");
            
            
            // 2.1.3
            // a) kf < 1
            double kf = 0.5;
            draw.DrawPlot(toDraw(fm, fn, kf, n, fs, zF), fs, "zf_a.png", FT.FFT);
            
            double[] zf = toDraw(fm, fn, kf, n, fs, zF);
            double[,] zfFFT = FT.FFT(zf);
            double[] zfMagnitude = Magnitude(zfFFT);
            double[] zfDecibel = FT.DB(zfMagnitude);
            draw.DrawPlotLog10(zfDecibel, fs, "zf_a_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 12)} Hz");
            
            // b) pi > kf > 0
            kf = Math.PI / 2;
            draw.DrawPlot(toDraw(fm, fn, kf, n, fs, zF), fs, "zf_b.png", FT.FFT);
            
            zf = toDraw(fm, fn, kf, n, fs, zF);
            zfFFT = FT.FFT(zf);
            zfMagnitude = Magnitude(zfFFT);
            zfDecibel = FT.DB(zfMagnitude);
            draw.DrawPlotLog10(zfDecibel, fs, "zf_b_widmo.png", FT.FFT);
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 12)} Hz");
            
            // c) kf > 2pi
            kf = 300 * Math.PI;
            draw.DrawPlotLog10(toDraw(fm, fn, kf, n, fs, zF), fs, "zf_c.png", FT.FFT);
            
            kf = 300300 * Math.PI;
            zf = toDraw(fm, fn, kf, n, fs, zF);
            zfFFT = FT.FFT(zf);
            zfMagnitude = Magnitude(zfFFT);
            zfDecibel = FT.DB(zfMagnitude);
            draw.DrawPlotLog10(zfDecibel, fs, "zf_c_widmo.png", FT.FFT);
            
            Console.WriteLine($"Szerokość pasma dla 3dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 3)} Hz");
            Console.WriteLine($"Szerokość pasma dla 6dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 6)} Hz");
            Console.WriteLine($"Szerokość pasma dla 12dB: {EstimateBandwidth(toDraw(fm, fn, kf, n, fs, zF), frequencies, 12)} Hz");
        }

        public static double[] Magnitude(double[,] fft)
        {
            int N = fft.GetLength(1);
            double[] magnitude = new double[N];

            for (int i = 0; i < N; i++)
            {
                magnitude[i] = Math.Sqrt(fft[0, i] * fft[0, i] + fft[1, i] * fft[1, i]);
            }

            return magnitude;
        }
        public static double[] CalculateFrequencies(int n, int fs)
        {
            double[] frequencies = new double[n];
            for (int i = 0; i < n; i++)
            {
                frequencies[i] = (double)i * fs / n;
            }
            return frequencies;
        }

        public static double EstimateBandwidth(double[] magnitudes, double[] freqs, double decibel)
        {
            double maxMagnitude = magnitudes.Max();
            // Dzielenie przez 20 skali decybelowej daje połowę magnitudy
            double dbHalf = decibel / 20;
            double threshold = maxMagnitude * Math.Pow(10, -dbHalf);

            int minIndex = 0, maxIndex = magnitudes.Length - 1;

            for (int i = 0; i < magnitudes.Length; i++)
            {
                if (magnitudes[i] >= threshold)
                {
                    minIndex = i;
                    break;
                }
            }

            for (int i = magnitudes.Length - 1; i >= 0; i--)
            {
                if (magnitudes[i] >= threshold)
                {
                    maxIndex = i;
                    break;
                }
            }

            return freqs[maxIndex] - freqs[minIndex];
        }


        public static double MT(double t, double fm)
        {
            // sygnal informacyjny
            double mt = Math.Sin(2 * Math.PI * fm * t);
            return mt;
        }

        public static double zA(double t, double fm, double fn, double ka)
        {
            double za = (ka * MT(t, fm) + 1) * Math.Cos(Math.PI * fn * t);
            return za;
        }
        public static double zP(double t, double fm, double fn, double kp)
        {
            double zp = Math.Cos(2 * Math.PI * fn * t + kp * MT(t, fm));
            return zp;
        }
        public static double zF(double t, double fm, double fn, double kf)
        {
            double zf = Math.Cos(2 * Math.PI * fn * t + kf / fm * MT(t, fm));
            return zf;
        }
        
        public delegate double SignalFunction(double t, double fm, double fn, double parameter);
        
        public static  double[] toDraw(double fm, double fn, double parameter, int n, int fs, SignalFunction signalFunction)
        {
            double[] results = new double[n];
            for (int i = 0; i < n; i++)
            {
                double t = (double)i / fs;
                results[i] = signalFunction(t, fm, fn, parameter);
            }
            return results;
        }
        
    }

    public static class draw
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
            plt.SavePng($"{name}", 1920, 1200);
        }
    
        public static void DrawPlotLog10(double[] input, double fs, string name, Func<double[], double[,]> transformFunction)
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
                ftHalf[i] = Math.Log10(ft[i]);
                FKHalf[i] = FK[i];
            }

            Plot plt = new Plot();
            plt.Add.Scatter(FKHalf, ftHalf);
            plt.XLabel("Frequency");
            plt.YLabel("Amplitude spectrum");
            plt.Title($"Spectrum FFT");
            plt.SavePng($"{name}", 1920, 1200);
        }
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
    }
}
