project(render)

set(RENDER_SOURCES 
	graphics.cpp
	${PUBLIC_DIR}/subsystem.cpp
	${PUBLIC_DIR}/subsystems.cpp
	${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(RENDER_EXPORTS)

add_library(render SHARED ${RENDER_SOURCES})

target_include_directories(render PUBLIC SDL3::SDL3 glad)
target_link_libraries(render PUBLIC SDL3::SDL3 glad)
