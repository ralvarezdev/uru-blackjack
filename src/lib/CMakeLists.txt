add_library(lib STATIC
cartas.cpp
cartas.h
clases.cpp
clases.h
terminal.cpp
terminal.h)

target_include_directories(lib PRIVATE ${CMAKE_CURRENT_LIST_DIR})