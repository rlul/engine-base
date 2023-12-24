project(launcher)

set(LAUNCHER_SOURCES 
    main.cpp
)

if(WIN32)
    add_executable(launcher WIN32 ${LAUNCHER_SOURCES})
else()
    add_executable(launcher ${LAUNCHER_SOURCES})
endif()

target_link_libraries(launcher engine)
