project(core)

set(CORE_SOURCES 
    commandline.cpp
    ${PUBLIC_DIR}/subsystems.cpp
	${PUBLIC_DIR}/subsystem.cpp
    ${PUBLIC_DIR}/common.cpp
)

add_compile_definitions(CORE_EXPORTS)

add_library(core SHARED ${CORE_SOURCES})
