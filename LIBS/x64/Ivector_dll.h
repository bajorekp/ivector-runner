#pragma once
#ifdef AGH_IVECTOR_DLL_EXPORTS
#define AGH_IVECTOR_DLL_API __declspec(dllexport) 
#else
#define AGH_IVECTOR_DLL_API __declspec(dllimport) 
#endif

#include <string>

namespace agh_ivex_export
{
	static void FillMsg(const std::string & _text, char* _dst, int _textlength);

	class IvExHandle
	{
	private:
		struct Ivex_heart;
		Ivex_heart * ivex_heart_ptr;
	public:
		IvExHandle();
		virtual ~IvExHandle();
		int GetIvectorSize();
		int Extract(double*  paudioSamples, int audioSamplesLengths/*in*/,
			double* pivector,/*out*/
			char* errorMsg, int errorMsgLength/*out*/
			);
	};
			
	//Create and return pointer to Ivector_extractor object
	extern "C" AGH_IVECTOR_DLL_API IvExHandle* CreateIvectorExtractor();

	//Dispose Ivector_extractor object
	extern "C" AGH_IVECTOR_DLL_API void DisposeIvectorExtractor(IvExHandle* _ivexh_ptr);

	//Get ivector size
	extern "C" AGH_IVECTOR_DLL_API int GetIvectorSize(IvExHandle* _ivexh_ptr);
		

	//Extract ivector using given audiosamples.Return Codes:
	// 0 - OK, 
	// 1 - warning(check errorMsg for more details),
	//-1 - error (check errorMsg for more details)	
	extern "C" AGH_IVECTOR_DLL_API int Extract(IvExHandle* _ivex_ptr,
		double*  paudioSamples, int audioSamplesLengths/*in*/,
		double* pivector,/*out*/
		char* errorMsg, int errorMsgLength/*out*/
		);

}