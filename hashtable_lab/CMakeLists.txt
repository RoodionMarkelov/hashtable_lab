# CMakeList.txt: проект CMake для hashtable_lab; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (hashtable_lab "hashtable_lab.cpp" "hashtable_lab.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hashtable_lab PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
