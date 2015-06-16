#include "IvectorExtractor.h"
#include <iostream>


IvectorExtractor::IvectorExtractor()
{
	//initialize library object
	this->ivex_ptr = agh_ivex_export::CreateIvectorExtractor();
	this->ivec_size = agh_ivex_export::GetIvectorSize(ivex_ptr);
}


IvectorExtractor::~IvectorExtractor()
{
	//Clean-up
	agh_ivex_export::DisposeIvectorExtractor(ivex_ptr);
}


std::vector<double> IvectorExtractor::GetIvector(std::vector<double> &audiosamples)
{
	//Check input
	if (audiosamples.size() < 20)
	{
		std::cout << "To few audiosamples for I-vector Extraction.";
		return std::vector < double >() ;
	}
		

	//Allocate memory
	std::vector<double> ivec(ivec_size);
	int errorMsgLength = 400;
	char* errorMsg = new char[errorMsgLength];

	//Extract i-vector	
	agh_ivex_export::Extract(ivex_ptr, &audiosamples[0], (int)audiosamples.size(), &ivec[0], errorMsg, errorMsgLength);
	return ivec;
}