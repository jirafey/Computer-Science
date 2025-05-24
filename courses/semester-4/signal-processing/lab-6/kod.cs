using System;

namespace Lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            Exercise1();
            Exercise2();
        }

        // Hamming encoder for 4 data bits into 7 encoded bits
        public static int[] HammingEncoder7to4(int[] input)
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

        // Hamming decoder for 7 encoded bits back to 4 data bits
        public static int[] HammingDecoder7to4(int[] input)
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

        // Exercise 1: Hamming encoding and decoding with examples
        public static void Exercise1()
        {
            int[] signal = { 1, 1, 0, 1 };

            Console.Write("Original signal:  ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            int[] encoded = HammingEncoder7to4(signal);

            Console.Write("\nEncoded signal: ");
            for (int i = 0; i < encoded.Length; i++)
            {
                Console.Write(encoded[i] + " ");
            }

            // Case I - No changes
            int[] decoded1 = HammingDecoder7to4(encoded);

            Console.WriteLine("\n\nCase I - No changes");
            Console.Write("Signal before: ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            Console.Write("\nSignal after:  ");
            for (int i = 0; i < decoded1.Length; i++)
            {
                Console.Write(decoded1[i] + " ");
            }

            // Case II - One random bit negated
            Random random = new Random();
            int randomIndex = random.Next(7);
            Console.WriteLine("\n\nRandom bit before: " + encoded[randomIndex]);

            encoded[randomIndex] ^= 1;

            Console.WriteLine("Random bit after:  " + encoded[randomIndex]);

            int[] decoded2 = HammingDecoder7to4(encoded);

            Console.WriteLine("\nCase II - One random bit negated");
            Console.Write("Signal before: ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            Console.Write("\nSignal after:  ");
            for (int i = 0; i < decoded2.Length; i++)
            {
                Console.Write(decoded2[i] + " ");
            }
            Console.WriteLine($"\nIndex of negated bit: {randomIndex}");
        }

        // Function to generate the P matrix
        public static int[][] GeneratePMatrix()
        {
            int[][] P = new int[11][];
            for (int i = 0; i < 11; i++)
            {
                P[i] = new int[4];
            }

            int offset;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 1; j <= 15; j++)
                {
                    if (j != 1 && j != 2 && j != 4 && j != 8)
                    {
                        if (j > 8) offset = 4;
                        else if (j > 4) offset = 3;
                        else offset = 2;

                        P[j - offset - 1][i] = (j >> i) % 2;
                    }
                }
            }
            return P;
        }

        // Function to generate the I matrix
        public static int[][] GenerateIMatrix(int n)
        {
            int[][] I = new int[n][];
            for (int i = 0; i < n; i++)
            {
                I[i] = new int[n];
                for (int j = 0; j < n; j++)
                {
                    I[i][j] = i == j ? 1 : 0;
                }
            }
            return I;
        }

        // Hamming encoding from 15 to 11 bits
        public static int[] HammingCode15to11(int[] signal)
        {
            // Hardcoded generator matrix P
            int[,] P = new int[11, 4] {
                {1, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 1, 0},
                {1, 1, 1, 0},
                {1, 0, 0, 1},
                {0, 1, 0, 1},
                {1, 1, 0, 1},
                {0, 0, 1, 1},
                {1, 0, 1, 1},
                {0, 1, 1, 1},
                {1, 1, 1, 1}
            };

            // Hardcoded identity matrix I
            int[,] I = new int[11, 11] {
                { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }
            };

            int[,] G = new int[11, 15];

            // Construct G matrix using P and I
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if (j < 4)
                        G[i, j] = P[i, j];
                    else
                        G[i, j] = I[i, j - 4];
                }
            }

            int[] c = new int[15];
            for (int i = 0; i < 15; i++)
            {
                c[i] = 0;
                for (int j = 0; j < 11; j++)
                {
                    c[i] += signal[j] * G[j, i];
                }
                c[i] %= 2;
            }

            return c;
        }

        // Transpose matrix function
        public static int[][] TransposeMatrix(int[][] matrix)
        {
            int numRows = matrix.Length;
            int numCols = matrix[0].Length;
            int[][] transposedMatrix = new int[numCols][];
            for (int i = 0; i < numCols; i++)
            {
                transposedMatrix[i] = new int[numRows];
                for (int j = 0; j < numRows; j++)
                {
                    transposedMatrix[i][j] = matrix[j][i];
                }
            }
            return transposedMatrix;
        }

        // Hamming decoding from 15 to 11 bits
        public static int[] HammingDecoder15to11(int[] c)
        {
            // Hardcoded parity check matrix H
            int[,] H = new int[4, 15] {
                { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0 },
                { 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0 },
                { 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }
            };

            // Hardcoded transposed parity check matrix HT
            int[,] HT = new int[15, 4];
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    HT[j, i] = H[i, j];
                }
            }

            int[] s = new int[4];
            for (int i = 0; i < 4; i++)
            {
                s[i] = 0;
                for (int j = 0; j < 15; j++)
                {
                    s[i] += c[j] * HT[j, i];
                }
                s[i] %= 2;
            }

            int S = (int)(s[0] * Math.Pow(2, 0) + s[1] * Math.Pow(2, 1) + s[2] * Math.Pow(2, 2) + s[3] * Math.Pow(2, 3));

            if (S != 0)
            {
                c[S - 1] ^= 1;
            }

            // Skipping parity bits and returning only information bits
            int[] x = new int[11];
            x[0] = c[2];
            x[1] = c[4];
            x[2] = c[5];
            x[3] = c[6];
            x[4] = c[8];
            x[5] = c[9];
            x[6] = c[10];
            x[7] = c[11];
            x[8] = c[12];
            x[9] = c[13];
            x[10] = c[14];

            return x;
        }

        // Exercise 2: Hamming encoding and decoding (15, 11) with examples
        public static void Exercise2()
        {
            int[] signal = { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0 };

            Console.Write("Original signal:  ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            int[] encoded = HammingCode15to11(signal);

            Console.Write("\nEncoded signal: ");
            for (int i = 0; i < encoded.Length; i++)
            {
                Console.Write(encoded[i] + " ");
            }

            // Case I - No changes
            int[] decoded1 = HammingDecoder15to11(encoded);

            Console.WriteLine("\n\nCase I - No changes");
            Console.Write("Signal before: ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            Console.Write("\nSignal after:  ");
            for (int i = 0; i < decoded1.Length; i++)
            {
                Console.Write(decoded1[i] + " ");
            }

            // Case II - One random bit negated
            Random random = new Random();
            int randomIndex = random.Next(15);

            Console.WriteLine("\n\nRandom bit before: " + encoded[randomIndex]);

            encoded[randomIndex] ^= 1;

            Console.WriteLine("Random bit after:  " + encoded[randomIndex]);

            int[] decoded2 = HammingDecoder15to11(encoded);

            Console.WriteLine("\nCase II - One random bit negated");
            Console.Write("Signal before: ");
            for (int i = 0; i < signal.Length; i++)
            {
                Console.Write(signal[i] + " ");
            }

            Console.Write("\nSignal after:  ");
            for (int i = 0; i < decoded2.Length; i++)
            {
                Console.Write(decoded2[i] + " ");
            }
        }
    }
}

