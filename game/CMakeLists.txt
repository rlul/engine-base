project(game)

set(GAME_SOURCES 
    baseentity.cpp
    basetile.cpp
    baseanimated.cpp
    baseplayer.cpp
    entitylist.cpp
    gameclient.cpp
    eventlistener.cpp
    eventsystem.cpp
    ent_darkmage.cpp
    ${PUBLIC_DIR}/subsystem.cpp
	${PUBLIC_DIR}/subsystems.cpp
    ${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(GAME_EXPORTS)

add_library(game SHARED ${GAME_SOURCES})

target_include_directories(game PUBLIC SDL2::SDL2)
target_link_libraries(game PUBLIC SDL2::SDL2)
