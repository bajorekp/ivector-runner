///
/// \author Bartlomiej Miga <bartek.miga@gmail.com>
/// \date 24.07.2013
///

#include "WaveHeader.h"
namespace AudioReader
{
	WaveHeader::WaveHeader( unsigned short channels )
		: _samplingRate( 48000u ),
		_audioFormat( 0x0001 ),
		_numChannels( channels ),
		_blockAlign( 2 * channels ),
		_bitsPerSample( 16 ),
		_byteRate( 48000 * 2 * 1 ),
		_subchunk1size( 16 ),
		_subchunk2size( 0 )
	{
		_chunkID[ 0 ] = 'R'; _chunkID[ 1 ] = 'I';
		_chunkID[ 2 ] = 'F'; _chunkID[ 3 ] = 'F';

		//_chunkSize = 4 + ( 8 + _subchunk1size + 8 + _subchunk2size );
		_chunkSize = 36 + _subchunk2size;

		_format[ 0 ] = 'W'; _format[ 1 ] = 'A';
		_format[ 2 ] = 'V'; _format[ 3 ] = 'E';

		_subchunk1ID[ 0 ] = 'f'; _subchunk1ID[ 1 ] = 'm';
		_subchunk1ID[ 2 ] = 't'; _subchunk1ID[ 3 ] = ' ';

		_subchunk2ID[ 0 ] = 'd'; _subchunk2ID[ 1 ] = 'a';
		_subchunk2ID[ 2 ] = 't'; _subchunk2ID[ 3 ] = 'a';

		_blockAlign = _numChannels * _bitsPerSample / 8;

	}	

	unsigned int WaveHeader::samplingRate( void ) const
	{
		return _samplingRate;
	}

	unsigned short WaveHeader::channels( void ) const
	{
		return _numChannels;
	}

	unsigned short WaveHeader::bitsPerSample( void ) const
	{
		return _bitsPerSample;
	}

	unsigned int WaveHeader::samplesCount( void ) const
	{
		return _subchunk2size / _blockAlign;
	}

	void WaveHeader::setBitsPerSample( unsigned short bitsPerSample )
	{
		_bitsPerSample = bitsPerSample;
		_blockAlign = _numChannels * _bitsPerSample / 8u;

		//_chunkSize = 4 + ( 8 + _subchunk1size + 8 + _subchunk2size );
		_chunkSize = 36 + _subchunk2size;
	}

	void WaveHeader::setChannels( unsigned short channels )
	{
		_numChannels = channels;
		_blockAlign = _numChannels * _bitsPerSample / 8u;
	}

	void WaveHeader::setSamplingRate( unsigned int samplingRate )
	{
		_samplingRate = samplingRate;
		_byteRate = samplingRate * 2u * _numChannels;
	}

	void WaveHeader::setSamplesCount( unsigned int samplesCount )
	{
		_subchunk2size = samplesCount * _blockAlign;
		_chunkSize = 36 + _subchunk2size;
	}

	bool WaveHeader::isValid( void ) const
	{
		return true;
	}

	void WaveHeader::reset( unsigned short channels )
	{
		_samplingRate = 48000u;
		_numChannels = channels;
		_blockAlign = 2 * channels;
		_bitsPerSample = 16;
		_byteRate = 48000u * 2u * 1u;
		_subchunk1size = 16;
		_subchunk2size = 0;
		_chunkSize = 36 + _subchunk2size;
	}

	std::ostream& operator<<( std::ostream& outputStream, const WaveHeader& header )
	{
		outputStream.write( header._chunkID, sizeof(header) );
		return outputStream;
	}

	std::istream& operator>>( std::istream& inputStream, WaveHeader& header )
	{
		inputStream.read( header._chunkID, sizeof(header) );
		return inputStream;
	}
}
