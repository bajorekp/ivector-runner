///
/// \class PcmBuffer
/// \author Bartlomiej Miga <bartek.miga@gmail.com>
/// \date 25.07.2013
///

#ifndef PCMBUFFER_H
#define PCMBUFFER_H

#include <vector>
#include <iostream>
namespace AudioReader
{
	class PcmBuffer;

	class PcmBuffer
	{
		friend std::istream& operator>>( std::istream&, PcmBuffer& );
		friend std::ostream& operator<<( std::ostream&, const PcmBuffer& );

	public:
		static const size_t DefaultBufferLength = 16192;

	public:
		PcmBuffer( size_t size = DefaultBufferLength );
		PcmBuffer( const PcmBuffer& other );

		~PcmBuffer( );

	public:
		///
		/// \returns
		///		size (capacity) of PcmBuffer
		///
		size_t size( ) const;

		///
		/// \returns
		///		numbers of stored samples
		///
		size_t stored( ) const;

		bool isFull( ) const;

		///
		/// Set number of stored data to 0. After that, the PcmBuffer still contains (propably invalid) data.
		///
		void clear( );

		size_t write( const std::vector< double >& data );
		size_t write( const short* data, size_t size );
		size_t write( const double* data, size_t size );

		///
		/// \returns
		///		pointer to internal data
		const short* data( ) const;

		const short& operator[ ]( size_t index ) const;
		short& operator[ ]( size_t index );

	private:
		size_t _stored;
		std::vector< short > _data;
	};
}
#endif