cmake_minimum_required(VERSION 2.8)

project(engine)        # Название проекта

set(SOURCE_LIB generator.cpp render.cpp types.cpp)   # Установка переменной со списком исходников

include_directories(Headers)

add_library(engine STATIC ${SOURCE_LIB})# Создание статической библиотеки