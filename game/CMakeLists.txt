project(game)

set(GAME_SOURCES 
    baseentity.cpp
    entitylist.cpp
)

add_compile_definitions(GAME_EXPORTS)

add_library(game SHARED ${GAME_SOURCES})

target_link_libraries(game PUBLIC)
