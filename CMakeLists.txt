cmake_minimum_required(VERSION 3.10)
project(MyMansion C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
file(GLOB GAME_SOURCES src/*.c)

if(EMSCRIPTEN)
    message(STATUS "Compilando para Web con Emscripten")

    if(DEFINED RAYLIB_INCLUDE_DIR)
        include_directories(${RAYLIB_INCLUDE_DIR})
    endif()
    if(DEFINED RAYLIB_LIBRARY)
        set(RAYLIB_LIBRARIES ${RAYLIB_LIBRARY})
    else()
        set(RAYLIB_LIBRARIES raylib)
    endif()

    add_executable(mansion ${GAME_SOURCES})

    # Copia assets al directorio de build antes del linkeo
    add_custom_command(TARGET mansion PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copiando assets al directorio de build..."
    )

    # El ejecutable queda en bin/, así que assets está un nivel arriba
    target_link_options(mansion PRIVATE
        "SHELL:-O2"
        "SHELL:-s USE_GLFW=3"
        "SHELL:-s ASYNCIFY=1"
        "SHELL:-s WASM=1"
        "SHELL:--preload-file ../assets"
    )

    target_link_libraries(mansion ${RAYLIB_LIBRARIES})

else()
    message(STATUS "Compilando para plataforma nativa")
    find_package(raylib 4.5 REQUIRED)
    add_executable(mansion ${GAME_SOURCES})
    target_link_libraries(mansion raylib m pthread dl rt X11)
endif()
