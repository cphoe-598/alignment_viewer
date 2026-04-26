cmake_minimum_required(VERSION 3.10)

project (alignment_viewer
  LANGUAGES CXX
)

# ----------------------------------------------------------------------------
# FTXUI section

# already downloaded git submodule

add_subdirectory(external/ftxui)

add_executable(av ./src/av.cpp)

target_link_libraries(av
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

