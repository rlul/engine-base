cmake_minimum_required(VERSION 3.10)

project(engine-demo)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)

# Определите директорию для сборки
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Добавьте подпроекты
add_subdirectory(engine)
add_subdirectory(launcher)
add_subdirectory(thirdparty/SDL)
