using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;
using NAudio.Wave;
namespace agh
{
    class FileManager
    {
        public static bool Save2TXT(List<double> data, string txtfname)
        {
            try
            {
                NumberFormatInfo nfi = new CultureInfo("en-US", false).NumberFormat;
                File.WriteAllLines(@txtfname,data.Select(d => d.ToString(nfi)).ToArray());
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return false;
            }
        }

        //Loads data stored in audio files using lef channel from stereo files. Works for 16-bit coded audio.
        public static bool LoadAudioData(string filepath, ref List<double> data)
        {
            try
            {
                WaveFileReader reader = new WaveFileReader(filepath);
                if (reader.WaveFormat.Channels>1)
                {
                    Console.WriteLine("Liczba kanałów w pliku {0} wynosi {1}. Dane zostaną pobrane tylko z pierwszego kanału.",
                        filepath, reader.WaveFormat.Channels);
                }
                if (reader.WaveFormat.SampleRate != 8000)
                {
                    Console.WriteLine("Częstotliwość próbkowania w pliku {0} wynosi {1}. System rozpoznawania mówcy jest skaliborawny do częstotliwości 8kHz. Plik został pominięty.",
                    filepath, reader.WaveFormat.Channels);
                    return false;
                }
                if (reader.Length < 0) return false;

                byte[] bufferIN = new byte[reader.Length];
                int read = reader.Read(bufferIN, 0, bufferIN.Length);

                int num_of_samples = (int)reader.SampleCount / reader.WaveFormat.Channels;
                var bytes_per_samples = (reader.WaveFormat.BitsPerSample / 8) * reader.WaveFormat.Channels;

                // data.Capacity = num_of_samples;
                // data = new double[num_of_samples]; 

                for (int i = 0; i < num_of_samples; i++)
                {
                    var sSampleL = BitConverter.ToInt16(bufferIN, i * bytes_per_samples);//convert samples to double values
                    data.Add(sSampleL / (sSampleL >= 0 ? 32767.0 : 32768.0));
                }

                reader.Dispose();

                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return false;
            }           
        }     
    }
}
