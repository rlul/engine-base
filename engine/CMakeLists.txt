project(engine)

set(ENGINE_SOURCES 
    enginemain.cpp
    engine.cpp
    scenesystem.cpp
    ${PUBLIC_DIR}/engine/iengine.h
    ${PUBLIC_DIR}/engine/iscenesystem.h
    ${PUBLIC_DIR}/engine/scene2d.cpp
    ${PUBLIC_DIR}/engine/scene2d.h
    ${PUBLIC_DIR}/common.cpp
    ${PUBLIC_DIR}/common.h
    ${PUBLIC_DIR}/engine/engine.h
)

add_compile_definitions(ENGINE_EXPORTS)

add_library(engine SHARED ${ENGINE_SOURCES})

target_link_libraries(engine PUBLIC subsystem core render SDL3::SDL3)
