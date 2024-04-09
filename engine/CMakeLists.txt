project(engine)

set(ENGINE_SOURCES 
	enginemain.cpp
	engine.cpp
	inputsystem.cpp
	tilemap.cpp
	tilelayer.cpp
	${PUBLIC_DIR}/subsystems.cpp
	${PUBLIC_DIR}/subsystem.cpp
	${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(ENGINE_EXPORTS)

add_library(engine SHARED ${ENGINE_SOURCES})

target_link_libraries(engine PUBLIC SDL2::SDL2 tmxlite)
