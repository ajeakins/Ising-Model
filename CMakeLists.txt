
cmake_minimum_required( VERSION 2.6 )

project( SingleSpinIsing )

set( CMAKE_CXX_FLAGS "-Wall -Werror -m64 -O3 -fPIC" )
add_definitions( -DSFMT_MEXP=19937 )

include_directories( . )

add_subdirectory( core )

add_subdirectory( test )

add_subdirectory( bind )