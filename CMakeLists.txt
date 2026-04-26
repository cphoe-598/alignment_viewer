cmake_minimum_required(VERSION 3.10)

project (alignment_viewer
  LANGUAGES CXX
)

# this directory currently includes an FTXUI Git submodule
add_subdirectory(external/ftxui)

FILE(GLOB_RECURSE Sources ./src/*.cpp)
add_executable(av ${Sources})

target_link_libraries(av
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

