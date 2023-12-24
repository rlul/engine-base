project(engine)

set(DESTINATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../game/bin/)
set(ENGINE_SOURCES 
    engine.cpp
    engine.h
)

add_compile_definitions(ENGINE_EXPORTS)

add_library(engine SHARED ${ENGINE_SOURCES})
