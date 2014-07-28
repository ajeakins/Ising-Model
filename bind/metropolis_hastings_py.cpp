#include <boost/python.hpp>

#include <core/lattice.h>
#include <core/metropolis_hastings.h>

#include "metropolis_hastings_py.h"

void registerMetropolisHastings()
{
	using namespace boost::python;

	/**
	 * Intialisation enum.
	 */

	enum_< Initialise >( "Initialise" )
		.value( "kRandom", kInitialise_Random )
		.value( "kPlusOne", kInitialise_PlusOne )
		.value( "kMinusOne", kInitialise_MinusOne )
	;

	/**
	 * Simple metropolis-hastings simulation class
	 */

	class_< MetropolisHastings >( "MetropolisHastings", init< size_t, Initialise >() )
		.def( "energyPerSpin", &MetropolisHastings::energyPerSpin )
		.def( "magnetisationPerSpin", &MetropolisHastings::magnetisationPerSpin )
		.def( "run", &MetropolisHastings::run )
		.def( "setTemperature", &MetropolisHastings::setTemperature )
		.def( "size", &MetropolisHastings::size )
		.def( "spin", &MetropolisHastings::spin )
		.def( "temperature", &MetropolisHastings::temperature )
	;
}