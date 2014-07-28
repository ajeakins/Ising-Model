
#include <boost/python.hpp>

#include "metropolis_hastings_py.h"

BOOST_PYTHON_MODULE( ising_model )
{
	registerMetropolisHastings();
}