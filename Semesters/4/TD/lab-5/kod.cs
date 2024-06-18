using ScottPlot;

class Program
{
    static void Main(string[] args)
    {
        string currentWorkingDirectory = "../../../images/figures";
        Directory.SetCurrentDirectory(currentWorkingDirectory);

        const double totalTime = 1;
        double samplingRate = 8000;
        int totalSamples = 8000;
        double amplitudeLow = 500;
        double amplitudeHigh = 1000;
        int frequencyFactor = 2;
        int[] bitSequence = { 1, 0, 1, 1, 0, 1, 0, 0, 1, 1 };
        
        int numberOfBits = bitSequence.Length;
        double durationPerBit = totalTime / numberOfBits;
        double samplesPerBit = durationPerBit * samplingRate;
        double baseFrequency = frequencyFactor / durationPerBit;

        var askSignal = GenerateSignal(bitSequence, samplesPerBit, samplingRate, baseFrequency, totalSamples, 
            SignalType.ASK, amplitudeLow, amplitudeHigh);
        Plotting.PlotSignal(askSignal, "ask_z", 2000);
        var demodulatedAsk = DemodulateASK(askSignal, samplesPerBit, baseFrequency, samplingRate, bitSequence.Length);
        Plotting.PlotDemodulatedSignals(demodulatedAsk, "ask");

        var pskSignal = GenerateSignal(bitSequence, samplesPerBit, samplingRate, baseFrequency, totalSamples, 
            SignalType.PSK);
        Plotting.PlotSignal(pskSignal, "psk_z", 2000);
        var demodulatedPsk = DemodulatePSK(pskSignal, samplesPerBit, baseFrequency, samplingRate, bitSequence.Length);
        Plotting.PlotDemodulatedSignals(demodulatedPsk, "psk");

        var fskSignal = GenerateSignal(bitSequence, samplesPerBit, samplingRate, baseFrequency, totalSamples, 
            SignalType.FSK, modulationIndex: frequencyFactor, bitDuration: durationPerBit);
        Plotting.PlotSignal(fskSignal, "fsk_z", 2000);
        var demodulatedFsk = DemodulateFSK(fskSignal, samplesPerBit, durationPerBit, baseFrequency, samplingRate, 
            bitSequence.Length, frequencyFactor);
        Plotting.PlotDemodulatedSignals(demodulatedFsk, "fsk", true);
        
        Plotting.CompareBitVectors(bitSequence, demodulatedAsk.detected.Select(x => (int)x).ToArray(), "porownanie_ask");
        Plotting.CompareBitVectors(bitSequence, demodulatedPsk.detected.Select(x => (int)x).ToArray(), "porownanie_psk");
        Plotting.CompareBitVectors(bitSequence, demodulatedFsk.detectedBits, "porownanie_fsk");





    }

    public static double[] GenerateSignal(int[] bits, double samplesPerBit, double fs, double baseFreq, int iloscProbek, SignalType signalType, double lowAmplitude = 0, double highAmplitude = 0, int modulationIndex = 0, double bitDuration = 0)
    {
        if (signalType == SignalType.ASK)
        {
            return GenerateASK(bits, samplesPerBit, fs, baseFreq, iloscProbek, lowAmplitude, highAmplitude);
        }
        else if (signalType == SignalType.PSK)
        {
            return GeneratePSK(bits, samplesPerBit, fs, baseFreq, iloscProbek);
        }
        else if (signalType == SignalType.FSK)
        {
            return GenerateFSK(bits, samplesPerBit, bitDuration, fs, iloscProbek, modulationIndex);
        }
        else
        {
            throw new ArgumentException("Invalid signal type");
        }
    }

    public static double[] GenerateASK(int[] bits, double samplesPerBit, double fs, double baseFreq, int iloscProbek, double lowAmplitude, double highAmplitude)
    {
        return GenerateModulatedSignal(bits, samplesPerBit, fs, baseFreq, iloscProbek, (bit, t) => bit == 1 ? highAmplitude * Math.Sin(2 * Math.PI * baseFreq * t) : lowAmplitude * Math.Sin(2 * Math.PI * baseFreq * t));
    }

    public static double[] GeneratePSK(int[] bits, double samplesPerBit, double fs, double baseFreq, int iloscProbek)
    {
        return GenerateModulatedSignal(bits, samplesPerBit, fs, baseFreq, iloscProbek, (bit, t) => Math.Sin(2 * Math.PI * baseFreq * t + (bit == 1 ? Math.PI : 0)));
    }

    public static double[] GenerateFSK(int[] bits, double samplesPerBit, double bitDuration, double fs, int iloscProbek, int modulationIndex)
    {
        double inputFreq1 = (modulationIndex + 1) / bitDuration;
        double inputFreq2 = (modulationIndex + 2) / bitDuration;
        return GenerateModulatedSignal(bits, samplesPerBit, fs, inputFreq1, inputFreq2, iloscProbek, (bit, t) => Math.Sin(2 * Math.PI * (bit == 1 ? inputFreq2 : inputFreq1) * t));
    }

    public static double[] GenerateModulatedSignal(int[] bits, double samplesPerBit, double fs, double inputFreq1, double inputFreq2, int iloscProbek, Func<int, double, double> modulationFunction)
    {
        double[] signal = new double[iloscProbek];
        int bitIndex = 0;

        for (int i = 0; i < iloscProbek; i++)
        {
            double t = i / fs;
            signal[i] = modulationFunction(bits[bitIndex], t);

            if (i > 0 && i % samplesPerBit == 0)
                bitIndex++;

            if (bitIndex >= bits.Length)
                break;
        }

        return signal;
    }

    public static double[] GenerateModulatedSignal(int[] bits, double samplesPerBit, double fs, double baseFreq, int iloscProbek, Func<int, double, double> modulationFunction)
    {
        return GenerateModulatedSignal(bits, samplesPerBit, fs, baseFreq, baseFreq, iloscProbek, modulationFunction);
    }

    static (double[] multiplied, double[] integrated, double[] detected) DemodulateASK(double[] input, double samplesPerBit, double baseFreq, double fs, int bitCount)
    {
        return Demodulate(input, samplesPerBit, baseFreq, fs, bitCount, 200000);
    }

    static (double[] multiplied, double[] integrated, double[] detected) DemodulatePSK(double[] input, double samplesPerBit, double baseFreq, double fs, int bitCount)
    {
        return Demodulate(input, samplesPerBit, baseFreq, fs, bitCount, 0);
    }

    static (double[] multiplied, double[] integrated, double[] detected) Demodulate(double[] input, double samplesPerBit, double baseFreq, double fs, int bitCount, double threshold)
    {
        double[] multipliedSignal = Times(input, baseFreq, fs);
        double[] integratedSignal = Integral(multipliedSignal, samplesPerBit);
        double[] detectedSignal = Binarizzation(integratedSignal, threshold);
        return (multipliedSignal, integratedSignal, detectedSignal);
    }

    static (double[] multiplied1, double[] multiplied2, double[] integrated1, double[] integrated2, double[] detected, int[] detectedBits) DemodulateFSK(double[] input, double samplesPerBit, double bitDuration, double baseFreq, double fs, int bitCount, int modulationIndex)
    {
        double inputFreq1 = (modulationIndex + 1) / bitDuration;
        double inputFreq2 = (modulationIndex + 2) / bitDuration;

        double[] multipliedSignal1 = Times(input, inputFreq1, fs);
        double[] multipliedSignal2 = Times(input, inputFreq2, fs);
        double[] integratedSignal1 = Integral(multipliedSignal1, samplesPerBit);
        double[] integratedSignal2 = Integral(multipliedSignal2, samplesPerBit);
        double[] detectedSignal = Minus(integratedSignal2, integratedSignal1);
        int[] decodedBits = Decode(detectedSignal, bitCount, samplesPerBit);

        return (multipliedSignal1, multipliedSignal2, integratedSignal1, integratedSignal2, detectedSignal, decodedBits);
    }

    static double[] Times(double[] input, double baseFreq, double fs)
    {
        double[] output = new double[input.Length];

        for (int i = 0; i < input.Length; i++)
        {
            double t = i / fs;
            output[i] = input[i] * Math.Sin(2 * Math.PI * baseFreq * t);
        }

        return output;
    }

    static double[] Integral(double[] input, double samplesPerBit)
    {
        double[] output = new double[input.Length];
        double sum = 0; 

        for (int i = 0; i < input.Length; i++)
        {
            if (i > 0 && i % samplesPerBit == 0)
                sum = 0;

            sum += input[i];
            output[i] = sum;
        }

        return output;
    }

    static double[] Binarizzation(double[] input, double limit)
    {
        double[] output = new double[input.Length];

        for (int i = 0; i < input.Length; i++)
        {
            if (input[i] > limit)
            {
                output[i] = 1;
            }
            else
            {
                output[i] = 0;
            }
        }

        return output;
    }

    static double[] Minus(double[] signal1, double[] signal2)
    {
        double[] outputSignal = new double[signal1.Length];

        for (int i = 0; i < signal1.Length; i++)
        {
            outputSignal[i] = signal1[i] - signal2[i];
        }

        return outputSignal;
    }

    static int[] Decode(double[] detectedSignal, int bitCount, double samplesPerBit)
    {
        int[] outputBits = new int[bitCount];

        for (int i = 0; i < bitCount; i++)
        {
            int start = (int)(i * samplesPerBit);
            int end = (int)((i + 1) * samplesPerBit);
            double sum = 0;

            for (int j = start; j < end; j++)
            {
                sum += detectedSignal[j];
            }

            outputBits[i] = sum > 0 ? 1 : 0;
        }

        return outputBits;
    }

    public static class Plotting
    {   
        public static void PlotBitVector(int[] bitVector, string title, string yAxisLabel)
        {
            var myPlot = new ScottPlot.Plot();

            double[] bitVectorDouble = bitVector.Select(bit => (double)bit).ToArray();
            double[] bitIndex = Enumerable.Range(0, bitVector.Length).Select(i => (double)i).ToArray();

            var sig = myPlot.Add.Signal(bitVectorDouble);

            myPlot.Axes.Left.Label.Text = yAxisLabel;
            myPlot.Axes.Left.Label.ForeColor = sig.Color;

            myPlot.Axes.Bottom.Label.Text = "Bit Index";
            myPlot.Title(title);

            myPlot.SavePng($"{title}.png", 1920, 1200);
        }

        public static void CompareBitVectors(int[] originalBits, int[] demodulatedBits, string titlePrefix)
        {
            PlotBitVector(originalBits, $"{titlePrefix}_original", "Original Bits");
            PlotBitVector(demodulatedBits, $"{titlePrefix}_demodulated", "Demodulated Bits");
        }
        public static void PlotSignal(double[] signal, string title, int length)
        {
            var plt = new Plot();
            int plotLength = Math.Min(length, signal.Length);
            double[] time = Enumerable.Range(0, plotLength).Select(i => i / 8000.0).ToArray(); // Assuming fs = 8000
            plt.Add.Scatter(time, signal.Take(plotLength).ToArray());
            plt.Title(title);
            plt.XLabel("Time (seconds)");
            plt.YLabel("Amplitude");
            plt.SavePng($"{title}.png", 1920, 1200);
        }

        public static void PlotDemodulatedSignals((double[] multiplied, double[] integrated, double[] detected) demodulated,
            string type)
        {
            PlotSignal(demodulated.multiplied, $"{type}_x", 2000);
            PlotSignal(demodulated.integrated, $"{type}_p", 2000);
            PlotSignal(demodulated.detected, $"{type}_c", 2000);
        }

        public static void PlotDemodulatedSignals(
            (double[] multiplied1, double[] multiplied2, double[] integrated1, double[] integrated2, double[] detected,
                int[] detectedBits) demodulated, string type, bool isFSK)
        {
            PlotSignal(demodulated.multiplied1, $"{type}_x1", 2000);
            PlotSignal(demodulated.multiplied2, $"{type}_x2", 2000);
            PlotSignal(demodulated.integrated1, $"{type}_p1", 2000);
            PlotSignal(demodulated.integrated2, $"{type}_p2", 2000);
            PlotSignal(demodulated.detected, $"{type}_p", 2000);
            PlotSignal(demodulated.detectedBits.Select(x => (double)x).ToArray(), $"{type}_c", 2000);
        }
    }

    public enum SignalType
    {
        ASK,
        PSK,
        FSK
    }
}

