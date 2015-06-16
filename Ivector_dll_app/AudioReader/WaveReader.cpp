///
/// \file WaveReader.cpp
/// \author Bartlomiej Miga
/// \date 24.02.2014
///

#include "WaveReader.h"
#include "PcmBuffer.h"
#include <stdexcept>
#include <vector>

namespace AudioReader
{
	WaveReader::WaveReader( const std::string& filePath )
	{
		_stream.open( filePath, std::ios::binary );
		if (!_stream)
		{
			throw std::runtime_error("Could not open "+ filePath + ".");
		}
		_stream >> _header;
	}

	size_t WaveReader::channels( ) const
	{
		return static_cast< size_t >( _header.channels( ) );
	}

	size_t WaveReader::length( ) const
	{
		return static_cast< size_t >( _header.samplesCount( ) );
	}

	size_t WaveReader::sampleRate( ) const
	{
		return static_cast< size_t >( _header.samplingRate( ) );
	}

	void WaveReader::readSamples( std::vector<double>& samples )
	{
		// skip the header
		_stream.clear();
		_stream.seekg(0, std::ios::beg );
		_stream.seekg( sizeof(_header), std::ios::beg );

		//size_t s = sizeof(_header);

		size_t samplsCount = _header.channels( ) * _header.samplesCount( );
		samples.resize( samplsCount );

		PcmBuffer buffer;
		size_t currentIdx = 0;

		while( !_stream.eof( ) && !_stream.fail( ) )
		{
			_stream >> buffer;
			if( buffer.stored( ) > 0 )
			{
				for( size_t i = 0; i < buffer.stored( ) && currentIdx < samplsCount; i++, currentIdx++ )
				{
					samples[ currentIdx ] = static_cast< double >( buffer[ i ] ) / 32768.0f;
				}
			}
		}
	}

	void WaveReader::readChannel( size_t channel, std::vector<double>& samples )
	{
		// skip the header
		_stream.clear();
		_stream.seekg( 0, std::ios::beg );
		_stream.seekg( sizeof(_header), std::ios::beg );

		size_t samplesCount = _header.samplesCount( );
		samples.resize( samplesCount );

		const size_t channels =  _header.channels( );
		PcmBuffer buffer( PcmBuffer::DefaultBufferLength * channels );
		size_t currentIdx = 0;
				
		while( !_stream.eof( ) && !_stream.fail( ) )
		{
			_stream >> buffer;
			if( buffer.stored( ) > 0 )
			{
				for( size_t i = 0 + channel; i < buffer.stored( ) && currentIdx < samplesCount; i += channels, currentIdx++ )
				{
					samples[ currentIdx ] = static_cast< double >( buffer[ i ] ) / 32768.0f;
				}
			}
		}
	}

	void WaveReader::readChannels( std::vector< std::vector<double> >& channels )
	{
		// skip the header
		_stream.clear();
		_stream.seekg( 40, std::ios::beg );

		const size_t channelsConut = _header.channels( );
		//const size_t samplesCount = _header.samplesCount( );

		channels.resize( channelsConut );

		PcmBuffer buffer( PcmBuffer::DefaultBufferLength * channelsConut );

		while( !_stream.eof( ) && !_stream.fail( ) )
		{
			_stream >> buffer;
			const size_t stored = buffer.stored( ) / channelsConut;
			if( stored > 0 )
			{
				for( size_t c = 0; c < channelsConut; c++ )
				{
					std::vector<double>& channel = channels[ c ];
					for( size_t i = 0; i < stored; i++ )
					{
						channel[ i ] = buffer[ i * channelsConut + c ];
					}
				}
			}
		}
	}
}
