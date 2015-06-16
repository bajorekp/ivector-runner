///
/// \author Bartlomiej Miga <bartek.miga@gmail.com>
/// \date 25.07.2013
///

#include "PcmBuffer.h"
#include <fstream>
#include <algorithm>
namespace AudioReader
{
	std::istream& operator>>( std::istream& input, PcmBuffer& buffer )
	{
		input.read( reinterpret_cast< char* >( &buffer._data[ 0 ] ), 
			sizeof( buffer._data[ 0 ] ) * buffer.size( ) );

		std::streamsize read = input.gcount( );

		buffer._stored = static_cast< size_t >( read ) / sizeof( short );

		return input;
	}

	std::ostream& operator<<( std::ostream& output, const PcmBuffer& buffer )
	{
		output.write( reinterpret_cast< const char* >( &buffer._data[ 0 ] ),
			sizeof( buffer._data[ 0 ] ) * buffer.stored( ) );

		return output;
	}

	PcmBuffer::PcmBuffer( size_t size )
		: _data( size, 0 ),
		_stored( 0 )
	{

	}

	PcmBuffer::PcmBuffer( const PcmBuffer& buffer )
		: _data( buffer.size( ), 0 ),
		_stored( buffer._stored )
	{
		_data.assign( buffer._data.begin( ), buffer._data.begin( ) + _stored );
	}

	PcmBuffer::~PcmBuffer( )
	{

	}

	bool PcmBuffer::isFull( ) const
	{
		return _stored == _data.size( );
	}

	size_t PcmBuffer::stored( ) const
	{
		return _stored;
	}

	size_t PcmBuffer::size( ) const
	{
		return _data.size( );
	}

	void PcmBuffer::clear( )
	{
		_stored = 0;
	}

	const short* PcmBuffer::data( ) const
	{
		return &_data[ 0 ];
	}

	size_t PcmBuffer::write( const std::vector< double >& input )
	{
		size_t available = _data.size( ) - _stored;

		auto destBegin = _data.begin( ) + _stored;
		auto sourceBegin = input.begin( );
		auto sourceEnd = input.end( );

		if( input.size( ) > available )
		{
			sourceEnd = sourceBegin + available;
		}

		std::transform(
			sourceBegin,
			sourceEnd,
			destBegin,
			[ ]( double sample ) -> short
		{
			return static_cast< short >( sample * 32767.0f );
		}
		);

		size_t stored_ = sourceEnd - sourceBegin;

		_stored += stored_;

		return stored_;
	}

	size_t PcmBuffer::write( const short* input, size_t size )
	{
		size_t available = _data.size( ) - _stored;

		auto destBegin = _data.begin( ) + _stored;
		auto sourceBegin = input;
		auto sourceEnd = input + size;

		if( size > available )
		{
			sourceEnd = sourceBegin + available;
		}

		std::copy(
			sourceBegin,
			sourceEnd,
			destBegin
			);

		size_t stored_ = sourceEnd - sourceBegin;

		_stored += stored_;

		return stored_;
	}

	size_t PcmBuffer::write( const double* input, size_t size )
	{
		size_t available = _data.size( ) - _stored;

		auto destBegin = _data.begin( ) + _stored;
		auto sourceBegin = input;
		auto sourceEnd = input + size;

		if( size > available )
		{
			sourceEnd = sourceBegin + available;
		}

		std::transform(
			sourceBegin,
			sourceEnd,
			destBegin,
			[ ]( double sample ) -> short
		{
			return static_cast< short >( sample * 32767.0f );
		}
		);

		size_t stored_ = sourceEnd - sourceBegin;

		_stored += stored_;

		return stored_;
	}

	const short& PcmBuffer::operator[ ]( size_t index ) const
	{
		return _data[ index ];
	}

	short& PcmBuffer::operator[ ]( size_t index )
	{
		return _data[ index ];
	}
}