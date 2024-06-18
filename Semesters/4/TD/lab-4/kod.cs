using System.Numerics;
using MathNet.Numerics.IntegralTransforms;
using ScottPlot;
namespace lab4;

public static class SK
{
    public static void Main(string[] args)
    {
        // 1.

        string cwd = "../../../images/figures";
        Directory.SetCurrentDirectory(cwd);
        // n = liczba bitów (B)
        int B = 20;
        double Tc = 1; // czas trwania całości
        double Tb = Tc / B; // czas trwania pojedynczego bitu [s]

        // Initialize BitArray with random 0s and 1s

        double[] bArray = { 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 };

        double A1 = 1;
        double A2 = 9;

        double W = 1000; // docelowa częstotliwość
        double fn1 = (W + 1) / Tb;
        double fn2 = (W + 2) / Tb;
        double fn = W * Math.Pow(Tb, -1); // 2000
        double fs = 8000;
        int N = (int)(fs * Tc);

        double[] askResults = fns.GenerateSignalArray(fns.ASK, bArray, N, fn, A1, A2, 0, fs);
        double[] pskResults = fns.GenerateSignalArray(fns.PSK, bArray, N, fn, 0, 0, 0, fs);
        double[] fskResults = fns.GenerateSignalArray(fns.FSK, bArray, N, fn1, fn2, 0, 0, fs);

        Console.WriteLine("\nASK Results:");
        for (int i = 0; i < B; i++)
        {
            Console.WriteLine(askResults[i]);
        }

        Console.WriteLine("\nPSK Results:");
        for (int i = 0; i < B; i++)
        {
            Console.WriteLine(pskResults[i]);
        }

        Console.WriteLine("\nFSK Results:");
        for (int i = 0; i < B; i++)
        {
            Console.WriteLine(fskResults[i]);
        }

        // 2.
        // Wygenerować dla W=2 oraz ich przebiegi czasowe (?)
        W = 2;
        // tylko przy generowaniu wykresu
        B = 10;
        Tc = 1;
        Tb = Tc / B;
        fn1 = (W + 1) / Tb;
        fn2 = (W + 2) / Tb;
        fn = W * Math.Pow(Tb, -1);
        
        double[] askResults2 = fns.GenerateSignalArray(fns.ASK, bArray, N, fn, A1, A2, 0, fs);
        double[] pskResults2 = fns.GenerateSignalArray(fns.PSK, bArray, N, fn, 0, 0, 0, fs);
        double[] fskResults2 = fns.GenerateSignalArray(fns.FSK, bArray, N, fn1, fn2, 0, 0, fs);
        draw.DrawPlot(askResults2, fs, "za");
        draw.DrawPlot(pskResults2, fs, "zp");
        draw.DrawPlot(fskResults2, fs, "zf");
        // 3.
        // Wygenerować w skali decybelowej, cały strumień bitowy. jak najwięcej prążków
        
        double[] askResults3 = fns.GenerateSignalArray(fns.ASK, bArray, N, fn, A1, A2, 0, fs);
        double[] pskResults3 = fns.GenerateSignalArray(fns.PSK, bArray, N, fn, 0, 0, 0, fs);
        double[] fskResults3 = fns.GenerateSignalArray(fns.FSK, bArray, N, fn1, fn2, 0, 0, fs);

        double[,] fftaskresults3 = FT.FFT(askResults3);
        double[,] fftfskresults3 = FT.FFT(fskResults3);
        double[,] fftpskresults3 = FT.FFT(pskResults3);

        double[] magnitudeask = FT.Magnitude(fftaskresults3);
        double[] magnitudefsk = FT.Magnitude(fftfskresults3);
        double[] magnitudepsk = FT.Magnitude(fftpskresults3);

        double[] decmagask = FT.DB(magnitudeask);
        double[] decmagfsk = FT.DB(magnitudefsk);
        double[] decmagpsk = FT.DB(magnitudepsk);
        
        draw.DrawPlotLog10(decmagask, fs, "za_widmo.png", FT.FFT);
        draw.DrawPlotLog10(decmagfsk, fs, "zf_widmo.png", FT.FFT);
        draw.DrawPlotLog10(decmagpsk, fs, "zp_widmo.png", FT.FFT);
        // 4.

        // Oszacować szerokość pasma B3dB B6dB B12dB
        double[] freqs = new double[N];
        for (int i = 0; i < N; i++)
        {
            freqs[i] = (double)i * fs / N;
        }
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudeask, freqs, 3));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudeask, freqs, 6));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudeask, freqs, 12));
        
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudefsk, freqs, 3));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudefsk, freqs, 6));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudefsk, freqs, 12));
        
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudepsk, freqs, 3));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudepsk, freqs, 6));
        Console.WriteLine(bandwith.EstimateBandwidth(magnitudepsk, freqs, 12));
        
        // string input = "Hello, World!";
        // string binaryString = ConvertAsciiToBinary(input);
        // Console.WriteLine(binaryString);
    }

    public static class fns
    {
        public static Func<double[], int, double, double, double, double, double> ASK = (b, n, fn, A1, A2, t) =>
        {
            double zat = -1000;
            if (b[n % b.Length] == 0)
            {
                zat = A1 * Math.Sin(2 * Math.PI * fn * t);
            }
            else if (b[n % b.Length] == 1)
            {
                zat = A2 * Math.Sin(2 * Math.PI * fn * t);
            }

            return zat;
        };

        // _/__ - placeholder for unused parameter
        public static Func<double[], int, double, double, double, double, double> PSK = (b, n, fn, _, __, t) =>
        {
            double zpt = -1000;
            if (b[n % b.Length] == 0)
            {
                zpt = Math.Sin(2 * Math.PI * fn * t);
            }
            else if (b[n % b.Length] == 1)
            {
                zpt = Math.Sin(2 * Math.PI * fn * t + Math.PI);
            }

            return zpt;
        };

        public static Func<double[], int, double, double, double, double, double> FSK = (b, n, fn1, fn2, _, t) =>
        {
            double zft = -1000;
            if (b[n % b.Length] == 0)
            {
                zft = Math.Sin(2 * Math.PI * fn1 * t);
            }
            else if (b[n % b.Length] == 1)
            {
                zft = Math.Sin(2 * Math.PI * fn2 * t);
            }

            return zft;
        };

        public static double[] GenerateSignalArray(
            Func<double[], int, double, double, double, double, double> fn,
            double[] b, int n, double p1, double p2, double p3, double p4,
            double fs)
        {
            double[] t = new double[n];
            double[] results = new double[n];

            for (int i = 0; i < n; i++)
            {
                t[i] = i / fs;
                results[i] = fn(b, i, p1, p2, p3, t[i]);
            }

            return results;
        }
    }

    public static class draw
    {
        public static void DrawPlot(double[] results, double fs, string title)
        {
            double[] t = new double[results.Length];
            for (int i = 0; i < results.Length; i++)
            {
                t[i] = i / fs;
            }

            var plt = new Plot();
            plt.Add.Scatter(t, results);
            plt.Title("");
            plt.YLabel("Modulation function signal");
            plt.XLabel("Frequency");
            plt.SavePng(title + ".png", 1920, 1200);
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
            plt.SavePng($"{name}", 1920, 1080);
        }
    }

    public static class convert
    {
        static string ConvertAsciiToBinary(string input)
        {
            string binaryString = "";

            foreach (char c in input)
            {
                if (char.IsAscii(c))
                {
                    int asciiValue = (int)c;

                    if (asciiValue >= 32 && asciiValue <= 127)
                    {
                        // Convert ASCII value to a binary representation of 7 bits
                        // If there are less than 7 digits left gets populated with zeros to the point it's 7 digits.
                        string binary = Convert.ToString(asciiValue, toBase: 2)
                            .PadLeft(totalWidth: 7, paddingChar: '0');
                        binaryString += binary;
                    }
                    else
                    {
                        binaryString += "[Out of bounds]";
                        break;
                    }
                }
                else
                {
                    binaryString += "[Not ASCII]";
                    break;
                }
            }

            return binaryString;
        }
    }

    public static class FT
    {
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
    }

    public static class bandwith
    {
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
    }
}
