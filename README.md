# alignment_viewer

A sequence alignment viewer for me to practice C++. This program generates a TUI powered by [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

> [!NOTE]
> Currently functional for small, non-interleaved (i.e., contiguous sequences) [Phylip files](https://en.wikipedia.org/wiki/PHYLIP).

## Usage

```bash
./av [PATH_TO_ALN_FILE]
```

## Requirements

-   [CMake](https://cmake.org/) >= 3.10
-   [Ninja](https://ninja-build.org/) >= 1.13.2-3

> May work with previous versions of either. These are just what I'm using.

## Installation

I use a crude script that runs CMake so I don't have to type it out every time. This script is included in this repository.

```bash
git clone https://github.com/cphoe-598/alignment_viewer.git
cd alignment_viewer
./run_cmake.sh
```

---

## Progress

### Last time

-   Adapted the FTXUI [`scrollable.cpp`](https://arthursonzogni.github.io/FTXUI/examples_2component_2scrollbar_8cpp-example.html) sample to achieve a single, fixed window that scrolls up/down + left/right. 

### To do (near future)

-   Make the color scheme customizable via a config file passed as an additional argument.
    -   Include a command line argument for coloring by "DNA" vs "AA" sequences.
-   I've decided I don't like the resizable window. I want it to automatically adjust to the size of the open terminal window.

### To do (distant future)

-   Make Phylip-reading module compatible with interleaved Phylip files.

