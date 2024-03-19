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
set(SDL_AUDIODRIVER ON)
set(SDL_JOYSTICK ON)
set(SDL_HAPTIC ON)
set(SDL_FILE ON)
set(SDL_FILESYSTEM ON)
set(SDL_POWER ON)
set(SDL_THREAD ON)
set(SDL_TIMERS ON)
set(SDL_LOADSO ON)
set(SDL_CPUINFO ON)
set(SDL_VIDEO_DRIVER_WAYLAND OFF)
set(SDL_VIDEO_DRIVER_COCOA OFF)
set(SDL_VIDEO_RENDER_OGL ON)
set(SDL_VIDEO_OPENGL_GLX ON)
set(SDL2_DISABLE_SDL2MAIN ON)
set(SDL_TEST OFF)
set(SDL2IMAGE_AVIF OFF)
set(SDL2IMAGE_BMP OFF)
set(SDL2IMAGE_GIF OFF)
set(SDL2IMAGE_JPG OFF)
set(SDL2IMAGE_JXL OFF)
set(SDL2IMAGE_LBM OFF)
set(SDL2IMAGE_PCX OFF)
set(SDL2IMAGE_PNG ON)
set(SDL2IMAGE_PNM OFF)
set(SDL2IMAGE_QOI OFF)
set(SDL2IMAGE_SVG OFF)
set(SDL2IMAGE_TGA OFF)
set(SDL2IMAGE_TIF OFF)
set(SDL2IMAGE_WEBP OFF)
set(SDL2IMAGE_XCF OFF)
set(SDL2IMAGE_XPM OFF)
set(SDL2IMAGE_XV OFF)

set(GAME_NAME "demo")
set(BIN_DIR ${CMAKE_SOURCE_DIR}/../game/bin/${OS}${BITS}${DEBUG_SUFFIX})
set(PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_compile_definitions(GAME_NAME="${GAME_NAME}" abstract_class=class)

add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(core)
add_subdirectory(render)
add_subdirectory(game)
add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_image)
add_subdirectory(thirdparty/imgui_cmake)
add_subdirectory(thirdparty/json)

set(TARGETS 
    launcher engine core render game SDL2 SDL2_image
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
