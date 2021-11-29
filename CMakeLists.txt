cmake_minimum_required(VERSION 3.10.2)

project(Mesa4K)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(Mesa4K src/Mesa4K.cpp src/SwissRanger.cpp)

## Link libmesasr
FIND_PATH( MESASR_INCLUDE_PATH libMesaSR.h
	/usr/include
	/usr/local/include
	/sw/include
	/opt/local/include
	DOC "The libMesaSR.h directory")
FIND_LIBRARY( MESASR_LIBRARY
	NAMES mesasr
	PATHS
	/usr/lib64
	/usr/lib
	/usr/local/lib64
	/usr/local/lib
	/sw/lib
	/opt/local/lib
	DOC "The libMesaSR library")
TARGET_LINK_LIBRARIES(Mesa4K ${MESASR_LIBRARY})
INCLUDE_DIRECTORIES(${MESASR_INCLUDE_PATH})

## Link OpenCV
find_package(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(Mesa4K ${OpenCV_LIBS})
