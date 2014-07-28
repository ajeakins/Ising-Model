
FIND_PACKAGE( Boost 1.45.0 )
IF( NOT Boost_FOUND )
	MESSAGE( FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?" )
ENDIF()

INCLUDE_DIRECTORIES( "${Boost_INCLUDE_DIRS}" "/usr/include/python2.7" )
SET( Boost_USE_STATIC_LIBS OFF )
SET( Boost_USE_MULTITHREADED ON )
SET( Boost_USE_STATIC_RUNTIME OFF )
FIND_PACKAGE( Boost 1.45.0 COMPONENTS python )

ADD_LIBRARY(
ising_model SHARED

register_py.cpp
metropolis_hastings_py.cpp
)

TARGET_LINK_LIBRARIES( ising_model core ${Boost_LIBRARIES} )
