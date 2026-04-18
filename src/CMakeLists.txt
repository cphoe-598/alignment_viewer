cmake_minimum_required(VERSION 3.5)

project (alignment_viewer)

# ----------------------------------------------------------------------------
# FTXUI section

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  # Replace with a version, tag, or commit hash
)

FetchContent_MakeAvailable(ftxui)

add_subdirectory(external/ftxui)

add_executable(main main.cpp)

target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

