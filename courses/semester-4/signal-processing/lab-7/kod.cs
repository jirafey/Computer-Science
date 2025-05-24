using System;
using System.Linq;
using OpenTK.Input;


static class Program
{
    static void Main(string[] args)
        {
        const double totalTime = 1;
        double samplingRate = 8000;
        int totalSamples = 8000;

        double amplitudeLow = 0.5;
        double amplitudeHigh = 1;
        int frequencyFactor = 2;
        int[] bitSequence = { 
            1, 0, 1, 0, 1, 1, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
            1, 0, 0, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 1, 0, 1, 1, 0, 0,
            0, 1
        };
        double snr = 10; // Signal to Noise Ratio in dB

        int numberOfBits = bitSequence.Length;
        double durationPerBit = totalTime / numberOfBits;
        double samplesPerBit = durationPerBit * samplingRate;
        double baseFrequency = frequencyFactor / durationPerBit;

        // Encode using Hamming (7,4)
        int[] encodedBits = EncodeHamming(bitSequence);

        // Console.WriteLine("Encoded Bits:");
        // for (int i = 0; i < encodedBits.Length; i++)
        // {
        //     Console.WriteLine($"{encodedBits[i]}");
        // }

        // Generate signals for ASK, PSK, FSK
        var askSignal = GenerateASK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples, amplitudeLow, amplitudeHigh);
        var pskSignal = GeneratePSK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples);
        var fskSignal = GenerateFSK(encodedBits, samplesPerBit, durationPerBit, samplingRate, totalSamples, frequencyFactor);

        // Demodulate ASK, PSK, and FSK signals as before
        var demodulatedAsk = DemodulateASK(askSignal, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
        var demodulatedPsk = DemodulatePSK(pskSignal, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
        var demodulatedFsk = DemodulateFSK(fskSignal, samplesPerBit, durationPerBit, baseFrequency, samplingRate, encodedBits.Length, frequencyFactor);
        
        var decodedAsk = DecodeHamming(demodulatedAsk.detected);

        var decodedPsk = DecodeHamming(demodulatedPsk.detected);
    
        var decodedFsk = DecodeHamming(demodulatedFsk.detectedBits);
        
        // // Output original and decoded bits
        // Console.WriteLine("Original\tASK Detected\tPSK Detected\tFSK Detected");
        // for (int i = 0; i < bitSequence.Length; i++)
        // {
        //     Console.WriteLine($"{bitSequence[i]}\t\t{decodedAsk[i]}\t\t{decodedPsk[i]}\t\t{decodedFsk[i]}");
        // }
        
        
        // // Compare the original bit sequence with the demodulated and decoded bit sequences
        // Console.WriteLine("Original\tASK Detected\tPSK Detected\tFSK Detected");
        // for (int i = 0; i < bitSequence.Length; i++)
        // {
        //     Console.WriteLine($"{bitSequence[i]}\t\t{demodulatedAsk.detected[i]}\t\t{demodulatedPsk.detected[i]}\t\t{demodulatedFsk.detectedBits[i]}");
        // }
        
        
// Zadanie 2

// koder nadmiarowy
        encodedBits = EncodeHamming(bitSequence);

// modulator
        askSignal = GenerateASK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples, amplitudeLow, amplitudeHigh);
        pskSignal = GeneratePSK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples);
        fskSignal = GenerateFSK(encodedBits, samplesPerBit, durationPerBit, samplingRate, totalSamples, frequencyFactor);

// Szum
        double[] alfaNoise = {0.1, 0.3, 0.5, 0.7, 0.9};

        Console.WriteLine("Zadanie 2: szum, alfa");

        foreach (var alfa in alfaNoise)
        {
            // Add noise to the signals
            (askSignal, pskSignal, fskSignal) = Noise(askSignal, pskSignal, fskSignal, alfa);

            // demodulator
            demodulatedAsk = DemodulateASK(askSignal, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedPsk = DemodulatePSK(pskSignal, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedFsk = DemodulateFSK(fskSignal, samplesPerBit, durationPerBit, baseFrequency, samplingRate, encodedBits.Length, frequencyFactor);

            // dekoder
            decodedAsk = DecodeHamming(demodulatedAsk.detected);
            decodedPsk = DecodeHamming(demodulatedPsk.detected);
            decodedFsk = DecodeHamming(demodulatedFsk.detectedBits);

            // Calculate BER
            var berAsk = CalculateBER(bitSequence, decodedAsk);
            var berPsk = CalculateBER(bitSequence, decodedPsk);
            var berFsk = CalculateBER(bitSequence, decodedFsk);

            // Print BER results
            Console.WriteLine($"Alfa: {alfa}");
            Console.WriteLine($"BER for noisy ASK: {berAsk}");
            Console.WriteLine($"BER for noisy PSK: {berPsk}");
            Console.WriteLine($"BER for noisy FSK: {berFsk}\n");
        }
        // // Output original and decoded bits
        // Console.WriteLine("Original\tASK Detected\tPSK Detected\tFSK Detected");
        // for (int i = 0; i < bitSequence.Length; i++)
        // {
        //     Console.WriteLine($"{bitSequence[i]}\t\t{decodedAsk[i]}\t\t{decodedPsk[i]}\t\t{decodedFsk[i]}");
        // }
        //
        //
        // // Compare the original bit sequence with the demodulated and decoded bit sequences
        // Console.WriteLine("Original\tASK Detected\tPSK Detected\tFSK Detected");
        // for (int i = 0; i < bitSequence.Length; i++)
        // {
        //     Console.WriteLine($"{bitSequence[i]}\t\t{demodulatedAsk.detected[i]}\t\t{demodulatedPsk.detected[i]}\t\t{demodulatedFsk.detectedBits[i]}");
        // }

        
        // // Zadanie 3
        
        // koder nadmiarowy
        encodedBits = EncodeHamming(bitSequence);
        
        // modulator
        askSignal = GenerateASK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples, amplitudeLow, amplitudeHigh);
        pskSignal = GeneratePSK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples);
        fskSignal = GenerateFSK(encodedBits, samplesPerBit, durationPerBit, samplingRate, totalSamples, frequencyFactor);
        Console.WriteLine($"Zadanie 3 Tłumienie beta");

          for (double beta = 1; beta <= 9; beta+=2)
        {
        // Attenuate the signals
        double[] attenuatedASK = AttenuateSignal(askSignal, beta, samplingRate);
        double[] attenuatedPSK = AttenuateSignal(pskSignal, beta, samplingRate);
        double[] attenuatedFSK = AttenuateSignal(fskSignal, beta, samplingRate);

        // Demodulate the attenuated signals
        var (demodulatedASK, detectedASK) = DemodulateASK(attenuatedASK, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
        var (demodulatedPSK, detectedPSK) = DemodulatePSK(attenuatedPSK, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
        var (demodulatedFSK, detectedFSK) = DemodulateFSK(attenuatedFSK, samplesPerBit, 1.0, baseFrequency, samplingRate, encodedBits.Length, frequencyFactor);

        // Decode Hamming
        int[] decodedASK = DecodeHamming(detectedASK);
        int[] decodedPSK = DecodeHamming(detectedPSK);
        int[] decodedFSK = DecodeHamming(detectedFSK);

        // Calculate BER
        double berASK = CalculateBER(bitSequence, decodedASK);
        double berPSK = CalculateBER(bitSequence, decodedPSK);
        double berFSK = CalculateBER(bitSequence, decodedFSK);

        // Print the results
        Console.WriteLine($"Beta: {beta}");
        Console.WriteLine($"BER for attenuated ASK: {berASK}");
        Console.WriteLine($"BER for attenuated PSK: {berPSK}");
        Console.WriteLine($"BER for attenuated FSK: {berFSK}");
    }
        
        // Encode using Hamming (7,4)
        encodedBits = EncodeHamming(bitSequence);

        // Generate signals for ASK, PSK, FSK
        askSignal = GenerateASK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples, amplitudeLow, amplitudeHigh);
        pskSignal = GeneratePSK(encodedBits, samplesPerBit, samplingRate, baseFrequency, totalSamples);
        fskSignal = GenerateFSK(encodedBits, samplesPerBit, durationPerBit, samplingRate, totalSamples, frequencyFactor);

        // Noise then attenuation (4.1)
        double[] alfaNoise4 = { 0.1, 0.5, 0.9 };
        Console.WriteLine("\n\nZadanie 4.1: Noise then attenuation");

    foreach (var alfa in alfaNoise4)
    {
        // Add noise to the signals
        var (noisyAskSignal, noisyPskSignal, noisyFskSignal) = Noise(askSignal, pskSignal, fskSignal, alfa);

        for (double beta = 1; beta <= 9; beta += 4)
        {
            // Attenuate the noisy signals
            double[] attenuatedNoisyAsk = AttenuateSignal(noisyAskSignal, beta, samplingRate);
            double[] attenuatedNoisyPsk = AttenuateSignal(noisyPskSignal, beta, samplingRate);
            double[] attenuatedNoisyFsk = AttenuateSignal(noisyFskSignal, beta, samplingRate);

            // Demodulate the signals
            demodulatedAsk = DemodulateASK(attenuatedNoisyAsk, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedPsk = DemodulatePSK(attenuatedNoisyPsk, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedFsk = DemodulateFSK(attenuatedNoisyFsk, samplesPerBit, durationPerBit, baseFrequency, samplingRate, encodedBits.Length, frequencyFactor);

            // Decode the signals
            decodedAsk = DecodeHamming(demodulatedAsk.detected);
            decodedPsk = DecodeHamming(demodulatedPsk.detected);
            decodedFsk = DecodeHamming(demodulatedFsk.detectedBits);

            // Calculate BER
            var berAsk = CalculateBER(bitSequence, decodedAsk);
            var berPsk = CalculateBER(bitSequence, decodedPsk);
            var berFsk = CalculateBER(bitSequence, decodedFsk);

            // Print results
            Console.WriteLine($"Alfa: {alfa}, Beta: {beta}");
            Console.WriteLine($"BER for noisy and attenuated ASK: {berAsk}");
            Console.WriteLine($"BER for noisy and attenuated PSK: {berPsk}");
            Console.WriteLine($"BER for noisy and attenuated FSK: {berFsk}\n");
        }
    }

    // Attenuation then noise (4.2)
    Console.WriteLine("Zadanie 4.2: Attenuation then noise");

    foreach (var alfa in alfaNoise4)
    {
        for (double beta = 1; beta <= 9; beta += 4)
        {
            // Attenuate the signals
            double[] attenuatedAsk = AttenuateSignal(askSignal, beta, samplingRate);
            double[] attenuatedPsk = AttenuateSignal(pskSignal, beta, samplingRate);
            double[] attenuatedFsk = AttenuateSignal(fskSignal, beta, samplingRate);

            // Add noise to the attenuated signals
            var (noisyAttenuatedAsk, noisyAttenuatedPsk, noisyAttenuatedFsk) = Noise(attenuatedAsk, attenuatedPsk, attenuatedFsk, alfa);

            // Demodulate the signals
            demodulatedAsk = DemodulateASK(noisyAttenuatedAsk, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedPsk = DemodulatePSK(noisyAttenuatedPsk, samplesPerBit, baseFrequency, samplingRate, encodedBits.Length);
            demodulatedFsk = DemodulateFSK(noisyAttenuatedFsk, samplesPerBit, durationPerBit, baseFrequency, samplingRate, encodedBits.Length, frequencyFactor);

            // Decode the signals
            decodedAsk = DecodeHamming(demodulatedAsk.detected);
            decodedPsk = DecodeHamming(demodulatedPsk.detected);
            decodedFsk = DecodeHamming(demodulatedFsk.detectedBits);

            // Calculate BER
            var berAsk = CalculateBER(bitSequence, decodedAsk);
            var berPsk = CalculateBER(bitSequence, decodedPsk);
            var berFsk = CalculateBER(bitSequence, decodedFsk);

            // Print results
            Console.WriteLine($"Alfa: {alfa}, Beta: {beta}");
            Console.WriteLine($"BER for attenuated and noisy ASK: {berAsk}");
            Console.WriteLine($"BER for attenuated and noisy PSK: {berPsk}");
            Console.WriteLine($"BER for attenuated and noisy FSK: {berFsk}\n");
        }
    }

    }

    // Method to generate white noise
    public static double[] generateWhiteNoise(int length, double amplitude)
    {
        Random rand = new Random();
        double[] noise = new double[length];
        for (int i = 0; i < length; i++)
        {
            noise[i] = amplitude * (rand.NextDouble() * 2 - 1); // Generates noise between -amplitude and +amplitude
        }
        return noise;
    }
    // Hamming Encoding
    public static int[] EncodeHamming(int[] input)
    {
        int totalBlocks = (input.Length + 3) / 4;
        int[] result = new int[totalBlocks * 7];
        for (int block = 0; block < totalBlocks; block++)
        {
            int[] blockInput = new int[4];
            for (int i = 0; i < 4; i++)
            {
                if (block * 4 + i < input.Length)
                {
                    blockInput[i] = input[block * 4 + i];
                }
            }
            int[] encodedBlock = EncodeHamming74(blockInput);
            for (int i = 0; i < 7; i++)
            {
                result[block * 7 + i] = encodedBlock[i];
            }
        }
        return result;
    }

    static int[] EncodeHamming74(int[] input) 
    {
        int[] result = new int[7];
        result[0] = input[0] ^ input[1] ^ input[3];
        result[1] = input[0] ^ input[2] ^ input[3];
        result[2] = input[0];
        result[4] = input[1];
        result[5] = input[2];
        result[6] = input[3];
        result[3] = input[1] ^ input[2] ^ input[3];
        return result;
    }

    public static int[] DecodeHamming(int[] input)
    {
        int totalBlocks = input.Length / 7;
        int[] result = new int[totalBlocks * 4];
        for (int block = 0; block < totalBlocks; block++)
        {
            int[] blockInput = new int[7];
            for (int i = 0; i < 7; i++)
            {
                blockInput[i] = input[block * 7 + i];
            }
            int[] decodedBlock = DecodeHamming74(blockInput);
            for (int i = 0; i < 4; i++)
            {
                result[block * 4 + i] = decodedBlock[i];
            }
        }
        return result;
    }

    public static int[] DecodeHamming74(int[] input)
    {
        int[] result = new int[4];
        int _x0 = input[0] ^ input[1] ^ input[3];
        int _x1 = input[0] ^ input[2] ^ input[3];
        int _x3 = input[1] ^ input[2] ^ input[3];

        int x0 = input[0] ^ input[1] ^ input[3];
        int x1 = input[0] ^ input[2] ^ input[3];
        int x3 = input[1] ^ input[2] ^ input[3];

        int tilde_x0 = x0 ^ _x0;
        int tilde_x1 = x1 ^ _x1;
        int tilde_x3 = x3 ^ _x3;

        int S = (int)Math.Pow(2, 0) * tilde_x0 + (int)Math.Pow(2, 1) * tilde_x1 + (int)Math.Pow(2, 2) * tilde_x3;
        if (S != 0)
        {
            input[S - 1] = input[S - 1] ^ 1;
        }

        result[0] = input[2];
        result[1] = input[4];
        result[2] = input[5];
        result[3] = input[6];
        return result;
    }

    // Generate ASK signal
    public static double[] GenerateASK(int[] bitSequence, double samplesPerBit, double samplingRate, double baseFrequency, int totalSamples, double amplitudeLow, double amplitudeHigh)
    {
        double[] signal = new double[totalSamples];
        for (int i = 0; i < bitSequence.Length; i++)
        {
            double amplitude = bitSequence[i] == 1 ? amplitudeHigh : amplitudeLow;
            for (int j = 0; j < samplesPerBit; j++)
            {
                int sampleIndex = i * (int)samplesPerBit + j;
                if (sampleIndex < totalSamples)
                {
                    signal[sampleIndex] = amplitude * Math.Sin(2 * Math.PI * baseFrequency * sampleIndex / samplingRate);
                }
            }
        }
        return signal;
    }

    // Generate PSK signal
    public static double[] GeneratePSK(int[] bitSequence, double samplesPerBit, double samplingRate, double baseFrequency, int totalSamples)
    {
        double[] signal = new double[totalSamples];
        for (int i = 0; i < bitSequence.Length; i++)
        {
            double phase = bitSequence[i] == 1 ? 0 : Math.PI;
            for (int j = 0; j < samplesPerBit; j++)        {
            int sampleIndex = i * (int)samplesPerBit + j;
            if (sampleIndex < totalSamples)
            {
                signal[sampleIndex] = Math.Sin(2 * Math.PI * baseFrequency * sampleIndex / samplingRate + phase);
            }
        }
    }
    return signal;
}

// Generate FSK signal
public static double[] GenerateFSK(int[] bitSequence, double samplesPerBit, double durationPerBit, double samplingRate, int totalSamples, double frequencyFactor)
{
    double[] signal = new double[totalSamples];
    for (int i = 0; i < bitSequence.Length; i++)
    {
        double frequency = bitSequence[i] == 1 ? frequencyFactor / durationPerBit : (frequencyFactor + 1) / durationPerBit;
        for (int j = 0; j < samplesPerBit; j++)
        {
            int sampleIndex = i * (int)samplesPerBit + j;
            if (sampleIndex < totalSamples)
            {
                signal[sampleIndex] = Math.Sin(2 * Math.PI * frequency * sampleIndex / samplingRate);
            }
        }
    }
    return signal;
}


// Add noise
public static double[] AddNoise(double[] signal, double snr)
{
    Random rand = new Random();
    double[] noisySignal = new double[signal.Length];
    double signalPower = signal.Select(x => x * x).Average();
    double noisePower = signalPower / Math.Pow(10, snr / 10);
    double noiseAmplitude = Math.Sqrt(noisePower);
    for (int i = 0; i < signal.Length; i++)
    {
        noisySignal[i] = signal[i] + noiseAmplitude * (rand.NextDouble() * 2 - 1);
    }
    return noisySignal;
}

// Attenuate signal
public static double[] AttenuateSignal(double[] signal, double beta, double samplingRate)
{
    double[] attenuatedSignal = new double[signal.Length];
    for (int i = 0; i < signal.Length; i++)
    {
        attenuatedSignal[i] = signal[i] * Math.Exp(-beta * i / samplingRate);
    }


    return attenuatedSignal;
}



static (double[] demodulated, int[] detected) DemodulateASK(double[] signal, double samplesPerBit, double baseFrequency, double samplingRate, int numberOfBits)
    {
        double[] demodulated = new double[signal.Length];
        int[] detected = new int[numberOfBits];
        for (int i = 0; i < numberOfBits; i++)
        {
            double sum = 0;
            for (int j = 0; j < samplesPerBit; j++)
            {
                int sampleIndex = i * (int)samplesPerBit + j;
                if (sampleIndex < signal.Length)
                {
                    demodulated[sampleIndex] = signal[sampleIndex] * Math.Sin(2 * Math.PI * baseFrequency * sampleIndex / samplingRate);
                    sum += demodulated[sampleIndex];
                }
            }
            detected[i] = sum > 0 ? 1 : 0;
        }
        return (demodulated, detected);
    }

    static (double[] demodulated, int[] detected) DemodulatePSK(double[] signal, double samplesPerBit, double baseFrequency, double samplingRate, int numberOfBits)
    {
        double[] demodulated = new double[signal.Length];
        int[] detected = new int[numberOfBits];
        for (int i = 0; i < numberOfBits; i++)
        {
            double sum = 0;
            for (int j = 0; j < samplesPerBit; j++)
            {
                int sampleIndex = i * (int)samplesPerBit + j;
                if (sampleIndex < signal.Length)
                {
                    demodulated[sampleIndex] = signal[sampleIndex] * Math.Sin(2 * Math.PI * baseFrequency * sampleIndex / samplingRate);
                    sum += demodulated[sampleIndex];
                }
            }
            detected[i] = sum > 0 ? 1 : 0;
        }
        return (demodulated, detected);
    }

    static (double[] demodulated, int[] detectedBits) DemodulateFSK(double[] signal, double samplesPerBit, double durationPerBit, double baseFrequency, double samplingRate, int numberOfBits, double frequencyFactor)
    {
        double[] demodulated = new double[signal.Length];
        int[] detectedBits = new int[numberOfBits];
        for (int i = 0; i < numberOfBits; i++)
        {
            double frequency1 = frequencyFactor / durationPerBit;
            double frequency2 = (frequencyFactor + 1) / durationPerBit;
            double sum1 = 0;
            double sum2 = 0;
            for (int j = 0; j < samplesPerBit; j++)
            {
                int sampleIndex = i * (int)samplesPerBit + j;
                if (sampleIndex < signal.Length)
                {
                    sum1 += signal[sampleIndex] * Math.Sin(2 * Math.PI * frequency1 * sampleIndex / samplingRate);
                    sum2 += signal[sampleIndex] * Math.Sin(2 * Math.PI * frequency2 * sampleIndex / samplingRate);
                }
            }
            detectedBits[i] = sum1 > sum2 ? 1 : 0;
        }
        return (demodulated, detectedBits);
    }

    public static (double[],double[],double[]) Noise(double[] askSignal, double[] pskSignal, double[] fskSignal, double alfaNoise)
    {
        int totalSamples = 8000;
        double[] szumask = generateWhiteNoise(askSignal.Length, 500);
        double[] szumpsk = generateWhiteNoise(pskSignal.Length, 500);
        double[] szumfsk = generateWhiteNoise(fskSignal.Length, 500);
        
        for (int i = 0; i < totalSamples; i++)
        {
            askSignal[i] += alfaNoise * szumask[i];
            pskSignal[i] += alfaNoise * szumpsk[i];
            fskSignal[i] += alfaNoise * szumfsk[i];
        }
        return (askSignal, pskSignal, fskSignal);
    }

// Calculate Bit Error Rate (BER)
    public static double CalculateBER(int[] originalBits, int[] receivedBits)
    {
        int minLength = Math.Min(originalBits.Length, receivedBits.Length);
        int errorCount = 0;
        for (int i = 0; i < minLength; i++)
        {
            if (originalBits[i] != receivedBits[i])
            {
                errorCount++;
            }
        }

        return (double)errorCount / minLength;
    }
}


