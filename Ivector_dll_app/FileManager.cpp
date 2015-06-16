#include "FileManager.h"
#include "WaveReader.h"

#include <map>
#include <string>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <thread>

using namespace std;

namespace dsp_agh
{
	std::vector<double> FileManager::LoadWavData(std::string _path)
	{		
		vector<double> samples;
		AudioReader::WaveReader wr(_path);
		//cout << i++ <<"/" <<audiofilelist.size() << ",";	
		size_t fs = wr.sampleRate();
		if 	(wr.channels()>1)
			std::cout <<"Number of channels in" + _path + " is " << wr.channels() << ". Samples from channel 1 will be read only."<<endl;

		//TO DO: Resampling into FS

		if (fs == 8000 && wr.length() > 0)
		{
			wr.readChannel(0,samples);
		}
		else
		{
			cout << "File " + _path + " aborted due to sampling frequency mismatch (8kHz required)."<<endl;
		}		

		return samples;
	}

	void FileManager::StoreResultIntoCSV(std::string out_filename,
			std::string timestamp, std::string target_name, std::string impostor_name, 
			std::string pd_file, std::string modelname, double likelihood)
	{
		std::ofstream resstr(out_filename.c_str(), std::ostream::app);
		string line = 
			timestamp + "," +
			target_name + "," +
			impostor_name + "," +
			pd_file + "," +
			modelname + "," +
			to_string(likelihood);
		resstr << line << endl;
		resstr.close();
	}

	void FileManager::StoreResultIntoCSV(std::string out_filename,
		std::string timestamp, std::string target_name, std::string impostor_name,
		std::string pd_file, std::string modelname, double likelihood, std::mutex &mtx)
	{
		std::lock_guard<std::mutex> locker(mtx);
		std::ofstream resstr(out_filename.c_str(), std::ostream::app);
		string line =
			timestamp + "," +
			target_name + "," +
			impostor_name + "," +
			pd_file + "," +
			modelname + "," +
			to_string(likelihood);
		resstr << line << endl;
		resstr.close();
	}
}