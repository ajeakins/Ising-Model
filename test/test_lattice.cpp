
#include <iostream>

#include <core/lattice.h>

/**
 * TODO: convert to proper test framework.
 */

void test_index_conversion()
{
	Lattice lattice( 2, kInitialise_PlusOne );
	size_t index;
	Lattice::XY xy;

	index = lattice.toIndex( 0, 0 );
	xy = lattice.fromIndex( index );
	assert( xy.x == 0 );
	assert( xy.y == 0 );

	index = lattice.toIndex( 1, 0 );
	xy = lattice.fromIndex( index );
	assert( xy.x == 1 );
	assert( xy.y == 0 );

	index = lattice.toIndex( 0, 1 );
	xy = lattice.fromIndex( index );
	assert( xy.x == 0 );
	assert( xy.y == 1 );

	index = lattice.toIndex( 1, 1 );
	xy = lattice.fromIndex( index );
	assert( xy.x == 1 );
	assert( xy.y == 1 );
}

void test_lattice_construction()
{
	Lattice lattice1( 2, kInitialise_PlusOne );
	assert( lattice1.spin( 0, 0 ) == 1 );
	assert( lattice1.spin( 0, 1 ) == 1 );
	assert( lattice1.spin( 1, 0 ) == 1 );
	assert( lattice1.spin( 1, 1 ) == 1 );

	assert( lattice1.magnetisation() == 4 );
	assert( lattice1.energy() == -16 );

	Lattice lattice2( 2, kInitialise_MinusOne );
	assert( lattice2.spin( 0, 0 ) == -1 );
	assert( lattice2.spin( 0, 1 ) == -1 );
	assert( lattice2.spin( 1, 0 ) == -1 );
	assert( lattice2.spin( 1, 1 ) == -1 );

	assert( lattice2.magnetisation() == -4 );
	assert( lattice2.energy() == -16 );

	Lattice lattice3( 10, kInitialise_Random );
}

void test_lattice_flip_spin()
{
	Lattice lattice1( 2, kInitialise_PlusOne );

	lattice1.flipSpin( 0, 0 );

	assert( lattice1.spin( 0, 0 ) == -1 );
	assert( lattice1.spin( 0, 1 ) == 1 );
	assert( lattice1.spin( 1, 0 ) == 1 );
	assert( lattice1.spin( 1, 1 ) == 1 );

	assert( lattice1.computeEnergy() == lattice1.energy() );
	assert( lattice1.computeMagnetisation() == lattice1.magnetisation() );

	lattice1.flipSpin( 0, 0 );

	assert( lattice1.spin( 0, 0 ) == 1 );
	assert( lattice1.spin( 0, 1 ) == 1 );
	assert( lattice1.spin( 1, 0 ) == 1 );
	assert( lattice1.spin( 1, 1 ) == 1 );

	assert( lattice1.computeEnergy() == lattice1.energy() );
	assert( lattice1.computeMagnetisation() == lattice1.magnetisation() );

	Lattice lattice2( 3, kInitialise_PlusOne );

	lattice2.flipSpin( 0, 0 );
	lattice2.flipSpin( 1, 1 );
	lattice2.flipSpin( 2, 0 );
	lattice2.flipSpin( 0, 2 );

	assert( lattice2.computeEnergy() == lattice2.energy() );
	assert( lattice2.computeMagnetisation() == lattice2.magnetisation() );
}

int main()
{
	test_index_conversion();
	//test_lattice_construction();
	test_lattice_flip_spin();

	return 0;
}