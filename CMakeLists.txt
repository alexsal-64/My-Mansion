cmake_minimum_required(VERSION 3.10)
project(MyMansion C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Busca raylib instalado en el sistema (puedes instalarlo con apt o build desde fuente)
find_package(raylib 4.5 REQUIRED)

include_directories(include)

add_executable(mansion src/main.c)
target_link_libraries(mansion raylib m pthread dl rt X11)
