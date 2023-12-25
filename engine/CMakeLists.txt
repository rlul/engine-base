project(engine)

set(ENGINE_SOURCES 
    engine.cpp
    ${PUBLIC_DIR}/engine/engine.h
)

add_compile_definitions(ENGINE_EXPORTS abstract_class=class)

add_library(engine SHARED ${ENGINE_SOURCES})
