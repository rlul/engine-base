cmake_minimum_required(VERSION 3.10)

project(imgui)

add_library(imgui STATIC
    ../imgui/imgui.h
    ../imgui/imconfig.h
    ../imgui/imgui_internal.h
    ../imgui/imstb_rectpack.h
    ../imgui/imstb_textedit.h
    ../imgui/imstb_truetype.h
    ../imgui/backends/imgui_impl_sdl2.h
    ../imgui/backends/imgui_impl_sdlrenderer2.h
    ../imgui/imgui.cpp
    ../imgui/imgui_draw.cpp
    ../imgui/imgui_widgets.cpp
    ../imgui/imgui_demo.cpp
    ../imgui/imgui_tables.cpp
    ../imgui/backends/imgui_impl_sdl2.cpp
    ../imgui/backends/imgui_impl_sdlrenderer2.cpp
)

target_include_directories(imgui PUBLIC ../imgui)
target_link_libraries(imgui PUBLIC SDL2::SDL2)
