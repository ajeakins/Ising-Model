# pragma once

#include <SFMT/SFMT.h>
#include <iostream>

#include "lattice.h"

class MetropolisHastings
{
public:
	MetropolisHastings( size_t size, Initialise initialise );

	/**
	 * Run the simulation.
	 *
	 * One compute step visits all the spins
	 * once.
	 */

	void run( unsigned int steps );

	/**
	 * Lattice Parameters
	 */

	size_t size() const
	{
		return m_lattice.size();
	}

	short int spin( size_t x, size_t y ) const
	{
		return m_lattice.spin( x, y );
	}

	float energyPerSpin() const
	{
		return m_lattice.energyPerSpin();
	}

	float magnetisationPerSpin() const
	{
		return m_lattice.magnetisationPerSpin();
	}

	/**
	 * Simulation parameters
	 */

	void setTemperature( float temperature )
	{
		m_temperature = temperature;
	}

	float temperature() const
	{
		return m_temperature;
	}

private:
	void compute();

	void compute( size_t x, size_t y );

private:
	/// Lattice of spins
	Lattice m_lattice;

	/// Current simulation temperature
	float m_temperature;

	/// Random number generator
	sfmt_t m_sfmt;
};