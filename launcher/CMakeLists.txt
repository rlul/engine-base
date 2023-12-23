project(launcher)

set(DESTINATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../game)

add_executable(launcher WIN32
    main.cpp
)

add_custom_command(TARGET launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:launcher> ${DESTINATION_DIR}
)