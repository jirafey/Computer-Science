using MathNet.Numerics.IntegralTransforms;
using ScottPlot;
using ScottPlot.WinForms;
using System;
using System.IO;
using System.Numerics;
using System.Windows.Forms;

namespace test
{
    public partial class Form1 : Form
    {
        private double fm;
        private double fn;
        private int n;
        private int fs;

        public Form1()
        {
            InitializeComponent();

            fs = 8000;
            n = 8000;
            fm = 120;
            fn = 1000;
            double ka = 6;
            double kp = 1.5;
            double kf = 1.5;

            // Set textboxes to default values
            textBoxFs.Text = fs.ToString();
            textBoxFm.Text = fm.ToString();
            textBoxFn.Text = fn.ToString();
            textBoxKa.Text = ka.ToString();
            textBoxKp.Text = kp.ToString();
            textBoxKf.Text = kf.ToString();

            // Set trackbars to match the default values
            trackBarFm.Value = (int)fn;
            trackBarFn.Value = (int)fm;
            trackBarKa.Value = (int)ka;
            trackBarKp.Value = (int)kp;
            trackBarKf.Value = (int)kf;
            trackBarFs.Value = fs;

            comboBox1.Items.Add("Amplitude Modulation");
            comboBox1.Items.Add("Phase Modulation");
            comboBox1.Items.Add("Frequency Modulation");
            comboBox1.SelectedIndex = 0; // Set a default selection
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;

            // Add items to the second combo box
            comboBox2.Items.Add("Log10");
            comboBox2.Items.Add("Normal");
            comboBox2.SelectedIndex = 0; // Set a default selection
            comboBox2.SelectedIndexChanged += comboBox2_SelectedIndexChanged;

            // Initialize class-level variables with the passed arguments
            this.fm = fm;
            this.fn = fn;
            this.n = n;
            this.fs = fs;

            // Event handlers for textboxes and trackbars

            textBoxFm.TextChanged += textBox_TextChanged;
            textBoxFn.TextChanged += textBox_TextChanged;
            textBoxKa.TextChanged += textBox_TextChanged;
            textBoxKp.TextChanged += textBox_TextChanged;
            textBoxKf.TextChanged += textBox_TextChanged;
            textBoxFs.TextChanged += textBox_TextChanged;

            trackBarFm.ValueChanged += trackBar_ValueChanged;
            trackBarFn.ValueChanged += trackBar_ValueChanged;
            trackBarKa.ValueChanged += trackBar_ValueChanged;
            trackBarKp.ValueChanged += trackBar_ValueChanged;
            trackBarKf.ValueChanged += trackBar_ValueChanged;
            trackBarFs.ValueChanged += trackBar_ValueChanged;

            // Initial plot
            Form1_Load(null, null);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string cwd = "../../../";
            Directory.SetCurrentDirectory(cwd);

            // Initial plot
            double ka = 0.99;
            draw.DrawPlotLog10(toDraw(fm, fn, ka, n, fs, zA), fs, formsPlot1, FT.FFT);
            draw.DrawTimePlot(toDraw(fm, fn, ka, n, fs, zA), fs, formsPlot2);
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

        public static double MT(double t, double fm)
        {
            // Signal information
            double mt = Math.Sin(2 * Math.PI * fm * t);
            return mt;
        }

        public static double zA(double t, double fm, double fn, double ka)
        {
            double za = (ka * MT(t, fm) + 1) * Math.Cos(2 * Math.PI * fn * t);
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

        public static double[] toDraw(double fm, double fn, double parameter, int n, int fs, SignalFunction signalFunction)
        {
            double[] results = new double[n];
            for (int i = 0; i < n; i++)
            {
                double t = (double)i / fs;
                results[i] = signalFunction(t, fm, fn, parameter);
            }
            return results;
        }

        private void UpdatePlot()
        {
            // Read values from textboxes
            if (!double.TryParse(textBoxFm.Text, out double fm) ||
                !double.TryParse(textBoxFn.Text, out double fn) ||
                !double.TryParse(textBoxKa.Text, out double ka) ||
                !double.TryParse(textBoxKp.Text, out double kp) ||
                !double.TryParse(textBoxKf.Text, out double kf) ||
                !int.TryParse(textBoxFs.Text, out int fs))
            {
                MessageBox.Show("Invalid input. Please enter numeric values.");
                return;
            }

            // Determine which modulation type is selected
            string selectedItem = comboBox1.SelectedItem.ToString();
            // Determine which modulation type is selected
            string selectedItem2 = comboBox2.SelectedItem.ToString();

            // Update plot based on selected modulation type
            switch (selectedItem)
            {
                case "Amplitude Modulation":
                    if (selectedItem2 == "Normal")
                    {
                        draw.DrawPlot(toDraw(fm, fn, ka, n, fs, zA), fs, formsPlot1, FT.FFT);

                    }
                    else
                    {
                        draw.DrawPlotLog10(toDraw(fm, fn, ka, n, fs, zA), fs, formsPlot1, FT.FFT);
                    }
                    draw.DrawTimePlot(toDraw(fm, fn, ka, n, fs, zA), fs, formsPlot2);
                    break;
                case "Phase Modulation":
                    if (selectedItem2 == "Normal")
                    {
                        draw.DrawPlot(toDraw(fm, fn, kp, n, fs, zP), fs, formsPlot1, FT.FFT);
                    }
                    else
                    {
                        draw.DrawPlotLog10(toDraw(fm, fn, kp, n, fs, zP), fs, formsPlot1, FT.FFT);

                    }
                    draw.DrawTimePlot(toDraw(fm, fn, kp, n, fs, zP), fs, formsPlot2);
                    break;
                case "Frequency Modulation":
                    if (selectedItem2 == "Normal")
                    {
                        draw.DrawPlot(toDraw(fm, fn, kf, n, fs, zF), fs, formsPlot1, FT.FFT);
                    }
                    else
                    {
                        draw.DrawPlotLog10(toDraw(fm, fn, kf, n, fs, zF), fs, formsPlot1, FT.FFT);

                    }
                    draw.DrawTimePlot(toDraw(fm, fn, kf, n, fs, zF), fs, formsPlot2);
                    break;
                default:
                    MessageBox.Show("Unknown selection");
                    break;
            }
        }

        private void UpdateTrackBarValues()
        {
            // Update textboxes based on trackbar values
            textBoxFm.Text = trackBarFm.Value.ToString();
            textBoxFn.Text = trackBarFn.Value.ToString();
            textBoxKa.Text = trackBarKa.Value.ToString();
            textBoxKp.Text = trackBarKp.Value.ToString();
            textBoxKf.Text = trackBarKf.Value.ToString();
            textBoxFs.Text = trackBarFs.Value.ToString();

            UpdatePlot();
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            UpdateTrackbars();
            UpdatePlot();
        }

        private void trackBar_ValueChanged(object sender, EventArgs e)
        {
            UpdateTrackBarValues();
        }

        private void UpdateTrackbars()
        {
            // Update trackbars based on textboxes values
            if (int.TryParse(textBoxFm.Text, out int fm))
            {
                trackBarFm.Value = fm;
            }
            if (int.TryParse(textBoxFn.Text, out int fn))
            {
                trackBarFn.Value = fn;
            }
            if (double.TryParse(textBoxKa.Text, out double ka))
            {
                trackBarKa.Value = (int)ka;
            }
            if (double.TryParse(textBoxKp.Text, out double kp))
            {
                trackBarKp.Value = (int)kp;
            }
            if (double.TryParse(textBoxKf.Text, out double kf))
            {
                trackBarKf.Value = (int)kf;
            }
            if (int.TryParse(textBoxFs.Text, out int fs))
            {
                trackBarFs.Value = fs;
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdatePlot();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdatePlot();
        }

        public static class draw
        {
            public static void DrawTimePlot(double[] input, double fs, FormsPlot formsPlot)
            {
                double[] time = new double[input.Length];
                for (int i = 0; i < input.Length; i++)
                {
                    time[i] = i / fs;
                }

                formsPlot.Plot.Clear();
                formsPlot.Plot.Add.Scatter(time, input);
                formsPlot.Plot.XLabel("Time (s)");
                formsPlot.Plot.YLabel("Amplitude");
                formsPlot.Plot.Title($"Time Domain Signal");
                formsPlot.Refresh();
            }

            public static void DrawPlotLog10(double[] input, double fs, FormsPlot formsPlot, Func<double[], double[,]> transformFunction)
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

                formsPlot.Plot.Clear(); // Clear any existing plots
                formsPlot.Plot.Add.Scatter(FKHalf, ftHalf);
                formsPlot.Plot.XLabel("Frequency");
                formsPlot.Plot.YLabel("Amplitude Spectrum (Log10)");
                formsPlot.Plot.Title("Spectrum FFT");
                formsPlot.Refresh(); // Refresh the plot to show the new data
            }

            public static void DrawPlot(double[] input, double fs, FormsPlot formsPlot, Func<double[], double[,]> transformFunction)
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

                formsPlot.Plot.Clear(); // Clear any existing plots
                formsPlot.Plot.Add.Scatter(FKHalf, ftHalf);
                formsPlot.Plot.XLabel("Frequency");
                formsPlot.Plot.YLabel("Amplitude Spectrum (Normal)");
                formsPlot.Plot.Title("Spectrum FFT");
                formsPlot.Refresh(); // Refresh the plot to show the new data
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
}