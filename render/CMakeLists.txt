project(render)

set(RENDER_SOURCES 
    graphics.cpp
    ${PUBLIC_DIR}/render/render.h
    ${PUBLIC_DIR}/render/igraphics.h
)

add_compile_definitions(RENDER_EXPORTS abstract_class=class)

add_library(render SHARED ${RENDER_SOURCES})
