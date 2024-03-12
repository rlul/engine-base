cmake_minimum_required(VERSION 3.10)

project(engine-base)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS "64")
else()
    set(BITS "32")
endif()

if(WIN32)
    set(OS "win")
elseif(UNIX AND NOT APPLE)
    set(OS "linux")
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_SUFFIX "d")
else()
    set(DEBUG_SUFFIX "")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)
set(SDL_AUDIODRIVER)
set(SDL_JOYSTICK)
set(SDL_HAPTIC)
set(SDL_FILE)
set(SDL_FILESYSTEM)
set(SDL_POWER)
set(SDL_THREAD)
set(SDL_TIMERS)
set(SDL_LOADSO)
set(SDL_CPUINFO)
set(SDL_VIDEO_DRIVER_WAYLAND 0)
set(SDL_VIDEO_DRIVER_COCOA 0)
set(SDL_VIDEO_RENDER_OGL 1)
set(SDL_VIDEO_OPENGL_GLX 1)

set(GAME_NAME "demo")
set(BIN_DIR ${CMAKE_SOURCE_DIR}/../game/bin/${OS}${BITS}${DEBUG_SUFFIX})
set(PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_compile_definitions(GAME_NAME="${GAME_NAME}" abstract_class=class)

add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(core)
add_subdirectory(render)
add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/imgui_cmake)

set(TARGETS 
    launcher engine core render SDL3-shared
)

add_custom_target(CopyFiles ALL
    COMMENT "Copying files to ${BIN_DIR}"
    DEPENDS ${TARGETS}
)

foreach(subproject IN ITEMS ${TARGETS})
    add_custom_command(TARGET CopyFiles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${subproject} to ${BIN_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${subproject}> ${BIN_DIR}
    )
    target_include_directories(${subproject} PUBLIC ${PUBLIC_DIR})
endforeach()
