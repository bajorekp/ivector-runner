using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ivector_extractor
{
    class Program
    {
        static void Main(string[] args)
        {
            agh.IvectorExtractorWrapper ie = new agh.IvectorExtractorWrapper();

            List<string> filenames = new List<string>(args);;
            if (args.Length == 0)
            {
                filenames.Add("1.wav");
            }

            for (int i = 0; i < filenames.Count; i++)
            {
                string fp = filenames[i];
                string outfp = fp + "ivecs";
                Console.Write((i+1).ToString() + ". Extraction from " + fp + "...");
                if (ie.Extract(fp, outfp))
                {
                    Console.Write("Done. Result saved into " + outfp + "\n");
                }
                else
                    Console.Write("FAILED!\n");
            }   
        }
    }
}
