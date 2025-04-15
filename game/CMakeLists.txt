project(game)

set(GAME_SOURCES 
    baseentity.cpp
    basetile.cpp
    baseanimated.cpp
    baseitem.cpp
    baseplayer.cpp
    darkmage.cpp
    entitylist.cpp
    gameclient.cpp
    gameviewport.cpp
    staticcamera.cpp
    followcamera.cpp
    eventlistener.cpp
    eventsystem.cpp
    ${PUBLIC_DIR}/subsystem.cpp
    ${PUBLIC_DIR}/subsystems.cpp
    ${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(GAME_EXPORTS)

add_library(game SHARED ${GAME_SOURCES})

target_include_directories(game PUBLIC SDL2::SDL2)
target_link_libraries(game PUBLIC SDL2::SDL2)
