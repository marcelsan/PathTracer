set( CMAKE_C_FLAGS "-Wall -g" )

file(GLOB SRCS *.c *.h)

add_executable( cg ${SRCS} )
