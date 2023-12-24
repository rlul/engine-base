cmake_minimum_required(VERSION 3.10)

project(engine-demo)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS "64")
else()
    set(BITS "32")
endif()

if(WIN32)
    set(OS "win")
elseif(UNIX AND NOT APPLE)
    set(OS "linux")
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

set(BIN_DIR ${CMAKE_SOURCE_DIR}/../game/bin/${OS}${BITS})

add_subdirectory(engine)
add_subdirectory(launcher)
add_subdirectory(thirdparty/SDL)

add_custom_target(CopyFiles ALL
    COMMENT "Copying files to ${BIN_DIR}"
    DEPENDS engine
)

foreach(subproject IN ITEMS launcher engine SDL3-shared)
    add_custom_command(TARGET CopyFiles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${subproject} to ${BIN_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${subproject}> ${BIN_DIR}
    )
endforeach()