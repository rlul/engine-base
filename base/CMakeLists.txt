project(base)

set(BASE_SOURCES 
    commandline.cpp
    ${PUBLIC_DIR}/base/base.h
    ${PUBLIC_DIR}/base/icommandline.h
)

add_compile_definitions(BASE_EXPORTS)

add_library(base SHARED ${BASE_SOURCES})
