project(core)

set(CORE_SOURCES 
    commandline.cpp
    filesystem.cpp
    ${PUBLIC_DIR}/core/icommandline.h
    ${PUBLIC_DIR}/core/ifilesystem.h
    ${PUBLIC_DIR}/core/module.h
)

add_compile_definitions(CORE_EXPORTS)

add_library(core SHARED ${CORE_SOURCES})
