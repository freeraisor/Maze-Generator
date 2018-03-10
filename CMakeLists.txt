cmake_minimum_required(VERSION 2.8)

project(maze)        # Название проекта

set(EXECUTABLE_NAME "maze")
add_executable(${EXECUTABLE_NAME} main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
include_directories(Headers)       # Расположение заголовочных файлов
add_subdirectory(Sources)          # Добавление подпроекта, указывается имя дирректории

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} engine ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
