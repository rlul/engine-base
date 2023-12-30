project(render)

set(RENDER_SOURCES 
    graphics.cpp
    graphicsapi.cpp
    graphicsapi.h
    ${PUBLIC_DIR}/render/render.h
    ${PUBLIC_DIR}/render/igraphics.h
)

add_compile_definitions(RENDER_EXPORTS)

add_library(render SHARED ${RENDER_SOURCES})

target_include_directories(render PUBLIC SDL3::SDL3)
target_link_libraries(render PUBLIC base SDL3::SDL3)
