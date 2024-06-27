using System;
using System.Numerics;

namespace lab_2;

public class run
{
    static void Main()
    {
        double[] samples = { 1, 2, 3, 4 };
        Complex[] result = FourierTransform.DFT(samples);

        foreach (Complex c in result)
        {
            Console.WriteLine(c);
        }
    }
    public class FourierTransform
    {
        public static Complex[] DFT(double[] samples)
        {
            int N = samples.Length;
            Complex[] output = new Complex[N];

            for (int k = 0; k < N; k++)
            {
                Complex sum = new Complex(0.0, 0.0);
                for (int n = 0; n < N; n++)
                {
                    double angle = (2 * Math.PI * k * n) / N;
                    sum += samples[n] * new Complex(Math.Cos(angle), -Math.Sin(angle));
                }

                output[k] = sum;
            }

            return output;
        }
    }
}

