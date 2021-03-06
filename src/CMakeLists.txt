CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include (src_list.cmake)

# Adding the icon to the windows executable
#if (WIN32) 
#	set(GAME_SRCS ${GAME_SRCS} roguelike.rc)
#endif()

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(GAME_SRCS ${GAME_SRCS} mac/SDLMain.h mac/SDLMain.m)
ENDIF ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
if (UNIX OR MINGW)
    # se for o g++ para *nix ou o MinGW para Windows:
    add_definitions(-Wall -ansi -U_FORTIFY_SOURCE -msse2 -std=c++11)
elseif (MSVC) 
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /W4 /wd4100 /wd4127 /wd4201 /wd4211 /wd4250 /wd4355 /wd4706 /arch:SSE2 /fp:fast /MP)
endif ()

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )


add_executable(roguelike ${GAME_SRCS} ${GENERATED_SRC})
target_link_libraries(roguelike ${UGDK_EXTERNAL_LIBRARIES})

set(GAME_LOCAL_DIR "./data")


CONFIGURE_FILE(
    "game/config.h.in"
    "game/config.h"
)

#Libs and dlls stuff in Windows, for compatibility.
if(WIN32)
	foreach(it ${dlls})
		add_custom_command(TARGET roguelike POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E remove -f "${CMAKE_SOURCE_DIR}/${it}"
			WORKING_DIRECTORY ../ COMMENT "Removing ${it} from the root.")
	endforeach(it ${dlls})
		
	foreach(it ${libs})
		add_custom_command(TARGET roguelike POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E remove -f "${CMAKE_SOURCE_DIR}/${it}"
			WORKING_DIRECTORY ../ COMMENT "Removing ${it} from the root.")
	endforeach(it ${libs})

	IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_custom_command(TARGET roguelike POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory "./lib64/" "./"
			WORKING_DIRECTORY ../ COMMENT "Copying relevant libs to the root")
	ELSE()
		add_custom_command(TARGET roguelike POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory "./lib/" "./"
			WORKING_DIRECTORY ../ COMMENT "Copying relevant libs to the root")
	ENDIF()
endif(WIN32)