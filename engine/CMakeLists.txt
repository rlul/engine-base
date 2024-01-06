project(engine)

set(ENGINE_SOURCES 
    enginemain.cpp
    engine.cpp
    engine.h
    ${PUBLIC_DIR}/engine/engine.h
    ${PUBLIC_DIR}/common.cpp
    ${PUBLIC_DIR}/common.h
)

add_compile_definitions(ENGINE_EXPORTS)

add_library(engine SHARED ${ENGINE_SOURCES})

target_link_libraries(engine PUBLIC render core)
