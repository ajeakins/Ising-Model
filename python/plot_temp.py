
import sys
sys.path.append( "/data/dev/ising_model/build/bind" )

import matplotlib.pyplot as plt
import ising_model

from numpy import arange

sim = ising_model.MetropolisHastings( 100, ising_model.Initialise.kRandom )

temps = []
energys = []
mags = []

for tempature in arange( 0, 3, 0.05 ):
	sim.setTemperature( tempature )
	sim.run( 20 )

	temps.append( tempature )
	energys.append( sim.energyPerSpin() )
	mags.append( sim.magnetisationPerSpin() )

plt.plot( temps, mags, "g-" )
plt.plot( temps, mags, "ro" )
plt.show()

