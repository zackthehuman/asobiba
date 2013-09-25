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

set(SQUIRREL_DIR "${PROJECT_SOURCE_DIR}/extlibs/squirrel")
set(SQUIRREL_FILES
    # Squirrel core
    ${SQUIRREL_DIR}/squirrel/sqapi.cpp
    ${SQUIRREL_DIR}/squirrel/sqbaselib.cpp
    ${SQUIRREL_DIR}/squirrel/sqclass.cpp
    ${SQUIRREL_DIR}/squirrel/sqcompiler.cpp
    ${SQUIRREL_DIR}/squirrel/sqdebug.cpp
    ${SQUIRREL_DIR}/squirrel/sqfuncstate.cpp
    ${SQUIRREL_DIR}/squirrel/sqlexer.cpp
    ${SQUIRREL_DIR}/squirrel/sqmem.cpp
    ${SQUIRREL_DIR}/squirrel/sqobject.cpp
    ${SQUIRREL_DIR}/squirrel/sqstate.cpp
    ${SQUIRREL_DIR}/squirrel/sqtable.cpp
    ${SQUIRREL_DIR}/squirrel/sqvm.cpp

    # Squirrel standard library
    ${SQUIRREL_DIR}/sqstdlib/sqstdaux.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdblob.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdio.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdmath.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdrex.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdstream.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdstring.cpp
    ${SQUIRREL_DIR}/sqstdlib/sqstdsystem.cpp
)

set(SQRAT_DIR "${PROJECT_SOURCE_DIR}/extlibs/sqrat")

set(INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${SQUIRREL_DIR}/include
  ${SQUIRREL_DIR}/squirrel
  ${SQUIRREL_DIR}/sqstdlib
  ${SQRAT_DIR}/include
)

source_group("Header Files" FILES ${ASOBIBA_HEADERS})
source_group("Source Files" FILES ${ASOBIBA_SOURCES})

add_executable(asobiba
  ${SQUIRREL_FILES}
  ${ASOBIBA_SOURCES}
  ${ASOBIBA_HEADERS}
)

include_directories(${INCLUDE_DIRS})

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#
# Copy content files to output directory
#
add_custom_command(
  TARGET asobiba
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to output directory."
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources" $<TARGET_FILE_DIR:asobiba>/resources
)

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


