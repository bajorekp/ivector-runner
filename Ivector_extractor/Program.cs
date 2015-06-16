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
            
            String fp = "1.wav";
            String outfp = fp + "ivecs";

            Console.Write("\n . Extraction from " + fp + "...");
            if (ie.Extract(fp, outfp))
            {
                Console.Write("Done.");
            }
            else
                Console.Write("FAILED!");
                
        }
    }
}
