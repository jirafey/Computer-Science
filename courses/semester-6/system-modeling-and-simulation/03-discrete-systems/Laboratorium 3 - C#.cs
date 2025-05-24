using System;
using System.Collections.Generic;

namespace WahadloCS
{
    class Program
    {
        static void Main(string[] args)
        {
            // Parametry modelu
            double krok = 0.01, maxTime = 100.0;
            double g = 10.0, l = 3.0, m = 10, k = 1.0;

            //---------METODA I
            // Listy przechowujące informacje o zmiannach położenia wahadła w czasie
            // Kąt musi być podany w radianach
            List<double> fi0 = new List<double>(new double[] { 90.0 * Math.PI / 180 }); 
            List<double> fi1 = new List<double>(new double[] { 0.0 });
            // Ze wzoru na 2 pochodną
            List<double> fi2 = new List<double>(new double[] { -Math.Sin(fi0[0]) * g / l - fi1[0] * k / m });
            List<double> times = new List<double>(new double[] { 0.0 });

            // Symulacja modelu - Euhler
            WahadloEuhler(krok, maxTime, g, l, m, k, ref fi0, ref fi1, ref fi2, ref times);

            //---------METODA II
            // Kąt musi być podany w radianach
            List<double> fi0RK = new List<double>(new double[] { 90.0 * Math.PI / 180 }); 
            List<double> fi1RK = new List<double>(new double[] { 0.0 });
            // Ze wzoru na 2 pochodną
            List<double> fi2RK = new List<double>(new double[] { -Math.Sin(fi0[0]) * g / l - fi1[0] * k / m }); 
            List<double> timesRK = new List<double>(new double[] { 0.0 });

            // Symulacja modelu - Runge-Kutta
            WahadloRKII(krok, maxTime, g, l, m, k, ref fi0RK, ref fi1RK, ref fi2RK, ref timesRK);
        }

        // Metoda Euhlera - niski czas obliczeń, niska dokładność
        static void WahadloEuhler(double krok, double maxTime, double g, double l, double m, double k,
            ref List<double> fi0, ref List<double> fi1, ref List<double> fi2, ref List<double> times)
        {
            int i = 0;
            for (double time = times[0] + krok; time <= maxTime; time += krok, i += 1)
            {
                fi0.Add(fi0[i] + fi1[i] * krok);
                fi1.Add(fi1[i] + fi2[i] * krok);
                // Ze wzoru na 2 pochodną
                fi2.Add(-Math.Sin(fi0[i + 1]) * g / l - fi1[i + 1] * k / m);
                times.Add(time);
            }
        }

        // Metoda Rungego-Kutty II rzędu - wysoka dokładność, bardziej kosztowna obliczeniowo
        static void WahadloRKII(double krok, double maxTime, double g, double l, double m, double k,
            ref List<double> fi0, ref List<double> fi1, ref List<double> fi2, ref List<double> times)
        {
            int i = 0;
            for (double time = times[0] + krok; time <= maxTime; time += krok, i += 1)
            {
                // K1
                // Obliczamy pkt. pośredni przy użyciu metody Euhlera
                double K1y0 = fi1[i] * krok;
                double K1y1 = fi2[i] * krok;

                double newX0 = fi0[i] + K1y0 * 0.5;
                double newX1 = fi1[i] + K1y1 * 0.5;

                double poch1tmp = newX1;
                double poch2tmp = -Math.Sin(newX0) * g / l - newX1 * k / m;

                // K2
                // Obliczamy pkt. konńcowy przy użyciu metody Euhlera
                double K2y0 = poch1tmp * krok;
                double K2y1 = poch2tmp * krok;

                fi0.Add(fi0[i] + K2y0);
                fi1.Add(fi1[i] + K2y1);
                // Ze wzoru na 2 pochodną
                fi2.Add(-Math.Sin(fi0[i + 1]) * g / l - fi1[i + 1] * k / m);
                times.Add(time);
            }
        }
    }
}
