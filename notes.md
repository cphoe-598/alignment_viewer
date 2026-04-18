# Notes because I'll forget everything tomorrow

## FTXUI

Minimal `main.cpp`.

```cpp
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
 
int main() {
  using namespace ftxui;
 
  Element document = hbox({
    text("left")   | border,
    text("middle") | border | flex,
    text("right")  | border,
  });
 
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
}
```

Clone starter respository.

```bash
git clone https://github.com/ArthurSonzogni/ftxui-starter
```

Get external library using CMake.

```cmake
cmake_minimum_required(VERSION 3.5)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  # Replace with a version, tag, or commit hash
)

FetchContent_MakeAvailable(ftxui)

project (FTXUI_test)

add_executable(main main.cpp)

target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
```

## Build using CMake

In `src/`, run the following:

```bash
cmake -S ./ -B ../build/
```

Navigate to `build/`, run `make`.

Executable will be in `build/`.
