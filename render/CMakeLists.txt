project(render)

set(RENDER_SOURCES 
    graphics.cpp
    ${PUBLIC_DIR}/render/igraphics.h
    ${PUBLIC_DIR}/engine/iscenesystem.h
    ${PUBLIC_DIR}/render/module.h
)

add_compile_definitions(RENDER_EXPORTS)

add_library(render SHARED ${RENDER_SOURCES})

target_include_directories(render PUBLIC SDL3::SDL3 glad)
target_link_libraries(render PUBLIC subsystem core SDL3::SDL3 glad)
