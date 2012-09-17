CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(roguelike CXX C)
set(roguelike_VERSION_MAJOR 0)
set(roguelike_VERSION_MINOR 0)
set(roguelike_VERSION_SUBMINOR 0)
SET(roguelike_FULL_VERSION "${roguelike_VERSION_MAJOR}.${roguelike_VERSION_MINOR}.${roguelike_VERSION_SUBMINOR} Alpha")

MESSAGE("== Roguelike -- version ${roguelike_FULL_VERSION} ==")

IF (UNIVERSAL)
  # Necessary for a Mac Universal Binary
  SET (CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
  SET (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
  SET (MACOSX_DEPLOYMENT_TARGET 10.5)
ENDIF (UNIVERSAL)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND UNIVERSAL)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.5")
ENDIF()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# FindUGDK
option (USE_EMBBEDED_UGDK "" OFF)
find_package(UGDK REQUIRED)
include_directories(${UGDK_INCLUDE_DIRS})
set(UGDK_EXTERNAL_LIBRARIES ${UGDK_LIBRARIES})

# Required for managing DLLS and LIBS in windows in subdirectory src
if(WIN32)
	file(GLOB dlls RELATIVE ${CMAKE_SOURCE_DIR} *.dll)
	file(GLOB libs RELATIVE ${CMAKE_SOURCE_DIR} *.lib)
endif(WIN32)
	
# The game binary.
add_subdirectory(src)