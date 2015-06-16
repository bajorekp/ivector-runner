using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace agh
{
    class IvectorExtractorWrapper
    {

        //DLL imports
        #region PInvokes 
        [DllImport("Ivector_dll.dll", EntryPoint = "CreateIvectorExtractor", 
            CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DLLCreateIvectorExtractor();

        [DllImport("Ivector_dll.dll", EntryPoint = "DisposeIvectorExtractor", 
            CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern void DLLDisposeIvectorExtractor(IntPtr _IvectorExtractorPointer);

        [DllImport("Ivector_dll.dll", EntryPoint = "GetIvectorSize",
           CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern int DLLGetIvectorSize(IntPtr _IvectorExtractorPointer);

        [DllImport("Ivector_dll.dll", EntryPoint = "Extract", 
            CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern int DLLExtract(IntPtr _IvectorExtractorPointer, 
            double [] audiosamples, int audiosamplesLength,
            double[] ivector,
            StringBuilder msg, int msgLength
            );
        #endregion PInvokes

        private IntPtr _native_ivex_ptr;  //Ivector Extractor Handle
        private int _ivectorSize;          //size of ivector

        public IvectorExtractorWrapper()
        {
            this._native_ivex_ptr = DLLCreateIvectorExtractor();
            this._ivectorSize = DLLGetIvectorSize(this._native_ivex_ptr);
        }

        ~IvectorExtractorWrapper()
        {
            DLLDisposeIvectorExtractor(this._native_ivex_ptr);
        }

        //Create and save ivector based on wav file.
        //Output model will be saved in modelspath directory.
        public bool Extract(string wavfname, string outfname)
        {
            //Load audio samples            
            List<double> audiosamples = new List<double>();
            if (!FileManager.LoadAudioData(wavfname, ref audiosamples)) 
            {
                Console.WriteLine("Nie można wczytać pliku {0}.",wavfname);
                return false;
            }
        
            //Extract ivector
            List<double> ivector = Extract(audiosamples);
            if (ivector.Count > 0)           
            {
                return (FileManager.Save2TXT(ivector, outfname));            
            }
            return false;                                
        }

        //Enroll ivector basing on audiosamples
        public List<double> Extract(List<double> audiosamples)
        {
            //Error message buffer
            int maxMsgLength = 250;
            StringBuilder msg = new StringBuilder(maxMsgLength);
            msg.AppendLine("xyz");

            //Prepare containers for ivector
            double[] ivector = new double[this._ivectorSize];           

            //Enroll ivector
            int error_c = DLLExtract(this._native_ivex_ptr,
                audiosamples.ToArray(), audiosamples.Count,
                ivector, msg, msg.Capacity);
            
            switch (error_c)
            {
                case 1:
                    Console.WriteLine("[WARNING]" + msg);
                    return new List<double>(ivector);
                case -1:
                    Console.WriteLine("[ERROR]" + msg);
                    return new List<double>();
                case 0:
                    return new List<double>(ivector);
                default:
                    return new List<double>();
            }
        }       
    }
}
