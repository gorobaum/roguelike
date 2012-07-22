CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(roguelike CXX C)
set(roguelike_VERSION_MAJOR 0)
set(roguelike_VERSION_MINOR 0)
set(roguelike_VERSION_SUBMINOR 0)
SET(roguelike_FULL_VERSION "${roguelike_VERSION_MAJOR}.${roguelike_VERSION_MINOR}.${roguelike_VERSION_SUBMINOR} Alpha")

MESSAGE("== Roguelike -- version ${roguelike_FULL_VERSION} ==")

# TODO: document why we need this.
cmake_policy(SET CMP0015 NEW)

IF (UNIVERSAL)
  # Necessary for a Mac Universal Binary
  SET (CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
  SET (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
  SET (MACOSX_DEPLOYMENT_TARGET 10.5)
ENDIF (UNIVERSAL)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND UNIVERSAL)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.5")
ENDIF()

# FindUGDK
add_subdirectory(externals/ugdk)
include_directories ("externals/ugdk/src")

add_subdirectory(src) # The game binary.
