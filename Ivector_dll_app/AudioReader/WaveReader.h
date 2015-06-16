///
/// \file WaveReader.h
/// \author Bartlomiej Miga
/// \date 24.02.2014
///

#ifndef WAVEREADER_H
#define WAVEREADER_H

#include <fstream>
#include <vector>
#include "WaveHeader.h"
namespace AudioReader
{
	enum Channel {L,R};

	/// 
	/// \class WaveReader
	///	\brief It reads wave file in PCM format
	///
	class WaveReader //: public AudioReader
	{

	public:
		WaveReader( const std::string& filePath );
		virtual ~WaveReader( ) { }

		///
		/// \returns
		///		number of channels
		///
		virtual size_t channels( ) const;

		///
		/// \returns
		///		number of samples for single channel
		///
		virtual size_t length( ) const;

		///
		/// \returns
		///		sampling frequency of audio file
		///
		virtual size_t sampleRate( ) const;

		///
		/// \param[ out ] samples
		///		all samples from audio file
		///
		virtual void readSamples( std::vector<double>& samples );

		///
		/// \param[ in ] channel
		///
		/// \param[ out ] samples
		///
		virtual void readChannel( size_t channel, std::vector<double>& samples );

		///
		/// \param[ out ] channels
		///
		virtual void readChannels( std::vector< std::vector<double> >& channels );

	private:
		WaveHeader _header;
		std::ifstream _stream;

	};
}

#endif