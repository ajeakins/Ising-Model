#pragma once

#include <stdlib.h>
#include <assert.h>
#include <iostream>

class Lattice;

std::ostream& operator<< ( std::ostream& stream, const Lattice& lattice );

/**
 * Lattice spin initialisation
 */

enum Initialise
{
	kInitialise_Random,
	kInitialise_PlusOne,
	kInitialise_MinusOne
};

/**
 * Lattice
 *
 * Container for an 2D array of spins of +/-1
 */

class Lattice
{
public:

	/**
	 * Struct for holding x and y
	 * components of index.
	 */

	struct XY
	{
		size_t x;
		size_t y;
	};

public:
	Lattice(
		size_t size,
		Initialise initialise,
		float ambient_magnetic_field = 0.0f );

	~Lattice();

	/**
	 * Lattice attributes
	 */

	size_t size() const
	{
		return m_size;
	}

	float ambient_magnetic_field() const
	{
		return m_ambient_magnetic_field;
	}

	/**
	 * Index utils
	 */

	size_t toIndex( size_t x, size_t y ) const
	{
		return x + ( m_size * y );
	}

	XY fromIndex( size_t i ) const
	{
		XY result;
		result.x = i % m_size;
		result.y = ( int )( i / m_size );
		return result;
	}

	/**
	 * Spin Interaction
	 */

	void flipSpin( size_t x, size_t y )
	{
		assert( x < m_size );
		assert( y < m_size );

		size_t index = toIndex( x, y );

		// update energy and magnetisation
		// TODO: avoid duplicate computeEnergyChange
		m_energy += computeEnergyChange( x, y );
		m_magnetisation -= 2 * m_data[ index ];

		// flip spin
		m_data[ index ] *= -1;
	}

	short int spin( size_t x, size_t y ) const
	{
		assert( x < m_size );
		assert( y < m_size );

		return m_data[ toIndex( x, y ) ];
	}

	/**
	 * Compute the change in lattice energy caused
	 * by the flipping of the spin x, y
	 */

	int computeEnergyChange( size_t x, size_t y ) const;

	/**
	 * Lattice variables
	 * These are stored as state varibles, compute methods
	 * are also provided for internal use and consistency
	 * checking.
	 */

	int energy() const
	{
		return m_energy;
	}

	float energyPerSpin() const
	{
		return ( float )m_energy / ( float )( m_size * m_size );
	}

	int computeEnergy() const;

	int magnetisation() const
	{
		return m_magnetisation;
	}

	float magnetisationPerSpin() const
	{
		return ( float )m_magnetisation / ( float )( m_size * m_size );
	}

	int computeMagnetisation() const;

private:
	int neighbourSum( size_t x, size_t y ) const;

private:
	/// Size of the data array
	size_t m_size;
	/// Array of 2D data stored as 1D Array
	short int* m_data;

	/// Ambient magnetic field
	float m_ambient_magnetic_field;

	/// Energy of the lattice
	int m_energy;
	/// Magnetisation of the lattice
	int m_magnetisation;
};


