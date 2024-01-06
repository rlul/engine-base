project(core)

set(CORE_SOURCES 
    commandline.cpp
    ${PUBLIC_DIR}/core/core.h
    ${PUBLIC_DIR}/core/icommandline.h
)

add_compile_definitions(CORE_EXPORTS)

add_library(core SHARED ${CORE_SOURCES})
