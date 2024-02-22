project(subsystem)

set(SUBSYSTEM_SOURCES 
    appsystemgroup.cpp
    ${PUBLIC_DIR}/subsystem/iappsystem.h
    ${PUBLIC_DIR}/subsystem/iappsystemgroup.h
    ${PUBLIC_DIR}/subsystem/module.h
)

add_compile_definitions(SUBSYSTEM_EXPORTS)

add_library(subsystem SHARED ${SUBSYSTEM_SOURCES})
