project(render)

set(RENDER_SOURCES 
	graphics.cpp
	debugoverlay.cpp
	sprite.cpp
	texture.cpp
	texturesystem.cpp
	${PUBLIC_DIR}/subsystem.cpp
	${PUBLIC_DIR}/subsystems.cpp
	${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(RENDER_EXPORTS)

add_library(render SHARED ${RENDER_SOURCES})

target_include_directories(render PUBLIC SDL2::SDL2 SDL2_image::SDL2_image imgui nlohmann_json::nlohmann_json)
target_link_libraries(render PUBLIC SDL2::SDL2 SDL2_image::SDL2_image imgui nlohmann_json::nlohmann_json)
