cmake_minimum_required ( VERSION 2.8 )
project ( Predictor )

set ( Predictor_VERSION_MAJOR 1 )
set ( Predictor_VERSION_MINOR 0 )

#if (EXISTS ./configuration/cmakevim.txt)
	include (${PROJECT_SOURCE_DIR}/config/vim.cmake)
#endif()


#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/devel/cmake ${CMAKE_MODULE_PATH})
set(BUILD_SHARED_LIBS ON)

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )

# Locations for compiled libraries and binaries
set ( LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib" )
set ( EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" )

find_package(Boost 1.55.0 REQUIRED COMPONENTS serialization)

set (KE_INSTALL_LIBRARY_DIR lib${LIBRARY_INSTALL_SUFFIX})
set (KE_INSTALL_INCLUDE_DIR include)


include_directories (
	"${Shogun_INCLUDEDIR}"
	)

add_subdirectory(src)
