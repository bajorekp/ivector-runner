///
/// \class WaveHeader
/// \author Bartlomiej Miga <bartek.miga@gmail.com>
/// \date 24.07.2013
///

#include <fstream>
namespace AudioReader
{
	class WaveHeader;

	std::ostream& operator<<( std::ostream&, const WaveHeader& );
	std::istream& operator>>( std::istream&, WaveHeader& );

	///
	///	\brief Header of wave file
	///	\note
	///		A client is responsible for setting valid data in header before saving wave to file
	///
	class WaveHeader
	{
		friend std::ostream& operator<<( std::ostream&, const WaveHeader& );
		friend std::istream& operator>>( std::istream&, WaveHeader& );

	public:
		WaveHeader( unsigned short channels = 1u );

		///
		/// Restore to default wave header
		///	
		void reset( unsigned short channels = 1u );

		///
		/// \returns
		///		true if header is valid, false otherwise
		///
		// TODO:
		// Implement it!
		bool isValid( void ) const;

		///
		/// \returns
		///		bits per sample in single channel
		///
		unsigned short bitsPerSample( void ) const;

		unsigned short channels( void ) const;
		unsigned int samplingRate( void ) const;

		///
		/// \returns
		///		samples count in wave file (length of single channel; (total time / sampling rate)
		///
		unsigned int samplesCount( void ) const;

		void setBitsPerSample( unsigned short bitsPerSample );
		void setChannels( unsigned short channels );
		void setSamplingRate( unsigned int samplingRate );
		void setSamplesCount( unsigned int samplesCount );

	private:
		//
		// Important!
		// Do not change the sequence of the following fields!
		//
		// begin
		char _chunkID[ 4 ];				// 0-3 big
		unsigned int _chunkSize;		// 4-7 little
		char _format[ 4 ];				// 8-11 big
		char _subchunk1ID[ 4 ];			// 12-15 big
		unsigned int _subchunk1size;	// 16-19 little
		unsigned short _audioFormat;	// 20-21 little
		unsigned short _numChannels;	// 22-23 little
		unsigned int _samplingRate;		// 24-27 little
		unsigned int _byteRate;			// 28-31 little
		unsigned short _blockAlign;		// 32-33 little
		unsigned short _bitsPerSample;	// 34-35 little
		char _subchunk2ID[ 4 ];			// 36-39 big
		unsigned int _subchunk2size;	// 40-43 little
		// end

	};
}