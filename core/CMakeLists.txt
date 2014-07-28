
set(
	SRC

	lattice.cpp
	metropolis_hastings.cpp
	../SFMT/SFMT.c
)

add_library(
	core_static STATIC
	${SRC}
	)

add_library(
	core SHARED
	${SRC}
	)