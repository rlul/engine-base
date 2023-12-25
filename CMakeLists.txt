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
set(PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public)
set(TARGETS 
    launcher engine render SDL3-shared
)

add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(render)
add_subdirectory(thirdparty/SDL)

add_custom_target(CopyFiles ALL
    COMMENT "Copying files to ${BIN_DIR}"
    DEPENDS ${TARGETS}
)

foreach(subproject IN ITEMS ${TARGETS})
    add_custom_command(TARGET CopyFiles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${subproject} to ${BIN_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${subproject}> ${BIN_DIR}
    )
    target_include_directories(${subproject} PUBLIC ${PUBLIC_DIR})
endforeach()
