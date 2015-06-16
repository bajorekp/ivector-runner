// Class that supports file management and common commands
//

//Marcin Witkowski AGH 2014-07 

#pragma once
#include <string>
#include <vector> 
#include <fstream>
#include <mutex>

#undef CreateDirectory

namespace dsp_agh
{	
	class FileManager
	{
	public:

		//Load audio data into Wave container
		static std::vector<double> LoadWavData(std::string _path);

		//Return name of path or file without extension and directory
		static std::string GetName(std::string _path);		

		//Store each result of crossvalidation
		static void StoreResultIntoCSV(std::string out_filename,
			std::string timestamp, std::string target_name, std::string impostor_name, 
			std::string pd_file, std::string modelname, double likelihood);

		//Store each result of crossvalidation in multithreaded environment
		static void StoreResultIntoCSV(std::string out_filename,
			std::string timestamp, std::string target_name, std::string impostor_name,
			std::string pd_file, std::string modelname, double likelihood, std::mutex &mtx);
		
		//Save vector of data into txt file
		template <class T>
		static void SaveVector2Txt(std::vector<T> &data, std::string datafile)
		{
			std::ofstream ofile (datafile,std::ofstream::binary);
			//ofile << scientific; //set flag to scientific format (with e)
			for (auto el : data)			
				ofile << el << std::endl;		
			ofile.close();
		}

		//Load vector of data from txt file
		template <class T>
		static  std::vector<T> LoadVectorfromTxt(std::string datafile)
		{
			std::vector<T> data;
			std::string line;
			std::ifstream infile (datafile);
			if (infile.is_open())
			{	 
				T temp;
				while (getline (infile,line))
				{
					line >> temp;
					data.push_back(temp);
				}							 
				infile.close();
			}
			return data;
		}	
	};
}

