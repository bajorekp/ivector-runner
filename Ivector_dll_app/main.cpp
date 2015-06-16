#include "IvectorExtractor.h"
#include "FileManager.h"
#include <string>
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
	//Create instance of Ivector Extractor
	IvectorExtractor ie;

	//Get WAV filepaths
	std::vector<std::string> filepaths;
	if (argc > 1)
		filepaths.assign(argv + 1, argv + argc); //from command line argument
	else
		filepaths.push_back(std::string("1.wav")); //hardcoded
	
	//For each file
	int count = 1;
	for (auto fp : filepaths)
	{
		std::cout << count++ << ". Extraction from " + fp + "...";		
		try
		{
			//Load audio data
			std::vector<double> audiosamples = dsp_agh::FileManager::LoadWavData(fp);

			//Extract ivector
			std::vector<double> ivector = ie.GetIvector(audiosamples);

			//Save ivector into text file
			if (ivector.size() > 0)
			{
				dsp_agh::FileManager::SaveVector2Txt(ivector, fp + "ivec");
				std::cout << "Done. Result saved into " + fp + "ivec" << std::endl;
			}
		}			
		catch (std::exception &e)
		{
			std::cout << "FAILED! " ;
			std::cout << e.what() << std::endl;
		}					
	}	
}