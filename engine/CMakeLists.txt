project(engine)

set(DESTINATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../game/bin/)

add_library(engine SHARED
    engine.cpp
)

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:engine> ${DESTINATION_DIR}
)