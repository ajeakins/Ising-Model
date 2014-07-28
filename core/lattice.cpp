
#include <stdexcept>
#include <iostream>
#include <SFMT/SFMT.h>

#include "lattice.h"

/**
 * Stream Operator
 */

std::ostream& operator<< ( std::ostream& stream, const Lattice& lattice )
{
	short int value;

	for ( size_t x = 0; x != lattice.size(); ++x )
	{
		for ( size_t y = 0; y != lattice.size(); ++y )
		{
			value = lattice.spin( x, y );

			// pad to account for the minus sign
			if ( value > 0 )
			{
				stream << " ";
			}

			stream << value << ", ";
		}
		stream << std::endl;
	}

	return stream;
}

/**
 * Lattice
 */

Lattice::Lattice(
	size_t size,
	Initialise initialise,
	float ambient_magnetic_field )
:
	m_size( size ),
	m_data( new short int[ size * size ] ),
	m_ambient_magnetic_field( ambient_magnetic_field )
{
	switch ( initialise )
	{
	case kInitialise_PlusOne:
		for ( size_t i = 0; i != size * size; ++i )
		{
			m_data[i] = 1;
		}
		break;
	case kInitialise_MinusOne:
		for ( size_t i = 0; i != size * size; ++i )
		{
			m_data[i] = -1;
		}
		break;
	case kInitialise_Random:
		sfmt_t sfmt;
		sfmt_init_gen_rand( &sfmt, 0 );
		for ( size_t i = 0; i != size * size; ++i )
		{
			m_data[i] = sfmt_genrand_real1( &sfmt ) > 0.5 ? 1 : -1;
		}
		break;
	}

	m_energy = computeEnergy();
	m_magnetisation = computeMagnetisation();
}

Lattice::~Lattice()
{
	delete[] m_data;
}

int Lattice::computeEnergyChange( size_t x, size_t y ) const
{
	int sum = neighbourSum( x, y );
	int delta = 2 * spin( x, y ) * ( sum + m_ambient_magnetic_field );
	return delta;
}

int Lattice::computeEnergy() const
{
	XY xy;
	int sum, energy = 0;

	for ( size_t i = 0; i != m_size * m_size; ++i )
	{
		xy = fromIndex( i );
		sum = neighbourSum( xy.x, xy.y );

		// result should by 0, +/-2, +/-4
		assert( ( sum % 2 ) == 0 );

		energy -= m_data[i] * ( ( sum / 2 ) + m_ambient_magnetic_field );
	}

	return energy;
}

int Lattice::computeMagnetisation() const
{
	int magnetisation = 0;
	for ( size_t i = 0; i != m_size * m_size; ++i )
	{
		magnetisation += m_data[i];
	}

	return magnetisation;
}

namespace
{
	/**
	 * Modulus handling negative numbers
	 */
	inline int mod( int a, int b)
	{
		int result = a % b;
		return result < 0 ? result + b : result;
	}
}

int Lattice::neighbourSum( size_t x, size_t y ) const
{
	assert( x < m_size );
	assert( y < m_size );

	int sum = 0;
	size_t i;

	// Use a special modulus function for the cases
	// where the result can be negative.

	// x, y - 1
	i = toIndex( x, mod( ( int )y - 1 , m_size ) );
	sum += m_data[i];

	// x - 1, y
	i = toIndex( mod( ( int )x - 1 , m_size ), y );
	sum += m_data[i];

	// x + 1, y
	i = toIndex( ( x + 1 ) % m_size, y );
	sum += m_data[i];

	// x, y + 1
	i = toIndex( x, ( y + 1 ) % m_size  );
	sum += m_data[i];

	return sum;
}
