cmake_minimum_required(VERSION 2.8.3)
project(asobiba)

# Asobiba Versions
set(ASOBIBA_VERSION_MAJOR 0)
set(ASOBIBA_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O")

set(ASOBIBA_SOURCES
    source/Main.cpp
    source/Particle.cpp
    source/ParticleSystem.cpp
)

set(ASOBIBA_HEADERS
    include/Main.hpp
    include/MathHelpers.hpp
    include/Particle.hpp
    include/ParticleSystem.hpp
)

source_group("Header Files" FILES ${ASOBIBA_HEADERS})
source_group("Source Files" FILES ${ASOBIBA_SOURCES})

add_executable(asobiba ${ASOBIBA_SOURCES} ${ASOBIBA_HEADERS})

include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/1)
#include_directories(${PROJECT_SOURCE_DIR}/include/2)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#
# Apple-specific stuff
#
if( APPLE )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++" )
  set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++" )
  set( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -stdlib=libc++" )
endif( APPLE )

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(asobiba ${SFML_LIBRARIES})
endif(SFML_FOUND)


