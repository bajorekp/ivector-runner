#pragma once
#include "Ivector_dll.h"
#include <vector>

class IvectorExtractor
{
private:
	agh_ivex_export::IvExHandle * ivex_ptr;
	int ivec_size;

public:
	IvectorExtractor();
	virtual ~IvectorExtractor();

	//Extract i-vector from audiosamples
	std::vector<double> GetIvector(std::vector<double> &audiosamples);
};

