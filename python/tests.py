
import sys
sys.path.append( "/data/dev/ising_model/build/bind" )

import ising_model

# TODO: convert to proper test framework

# Test construction and method calls
def basicTest():

	# construction
	lattice = ising_model.MetropolisHastings( 2, ising_model.Initialise.kPlusOne )

	# size
	assert( lattice.size() == 2 )

	# spin reading
	assert( lattice.spin( 0, 0 ) == 1 )

	# lattice vars
	assert( lattice.energyPerSpin() != None )
	assert( lattice.magnetisationPerSpin() != None )

	# run a sim step
	lattice.run( 1 )

	# test setting and getting temperature
	lattice.setTemperature( 1 )
	assert( lattice.temperature() == 1 )

	lattice.setTemperature( 2 )
	assert( lattice.temperature() == 2 )

if __name__ == "__main__":
	basicTest()