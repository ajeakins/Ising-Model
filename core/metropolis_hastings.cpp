
#include <math.h>

#include "metropolis_hastings.h"

MetropolisHastings::MetropolisHastings(
	size_t size,
	Initialise initialise
	)
:
	m_lattice( size, initialise ),
	m_temperature( 0 )
{
	sfmt_init_gen_rand( &m_sfmt, 0 );
}

void MetropolisHastings::run( unsigned int steps )
{
	for ( unsigned int i = 0; i != steps; ++i )
	{
		compute();
	}
}

/**
 * Compute a single step updating every
 * spin.
 */

void MetropolisHastings::compute()
{
	for ( size_t x = 0; x != m_lattice.size(); ++x )
	{
		for ( size_t y = 0; y != m_lattice.size(); ++y )
		{
			compute( x, y );
		}
	}
}

/**
 * Compute a single single spin update.
 */

void MetropolisHastings::compute( size_t x, size_t y )
{
	float diff = m_lattice.computeEnergyChange( x, y );
	if ( diff <= 0 )
	{
		m_lattice.flipSpin( x, y );
	}
	else
	{
		double random = sfmt_genrand_real1( &m_sfmt );
		double expon = exp( -1.0f * diff / m_temperature );
		if ( random <= expon )
		{
			m_lattice.flipSpin( x, y );
		}
	}
}
