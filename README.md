# alignment_viewer

A sequence alignment viewer for me to practice C++. This program generates a TUI powered by [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

> [!NOTE]
> Program functional for small, non-interleaved (i.e., contiguous sequences) Phylip files.

## Usage

```bash
./av [PATH_TO_ALN_FILE]
```

Program takes a path to a file in alignment format (currently only takes [Phylip format](https://en.wikipedia.org/wiki/PHYLIP)).

The program parses the file, and displays sequence identifiers and sequences to the console.

## Requirements

-   [CMake](https://cmake.org/) >= 3.10
-   [Ninja](https://ninja-build.org/) >= 1.13.2-3

> May work with previous versions of either. These are just what I'm using.

## Installation

Clone this repository, then run the crude cmake script. An executable `av` will be located in the `build` directory.

```bash
git clone https://github.com/cphoe-598/alignment_viewer.git
cd alignment_viewer
./run_cmake.sh
```

---

## Current features

-   Sequences are displayed in a resizable and scrollable window.
-   Sequences are color-mapped by nucleotide.

## Progress

### Last time

-   Adapted the FTXUI [`scrollable.cpp`](https://arthursonzogni.github.io/FTXUI/examples_2component_2scrollbar_8cpp-example.html) sample to achieve a single, fixed window that scrolls up/down + left/right. 

### Next up (near future)

-   As last time I did little more than copy-paste the FTXUI `scrollable.cpp` sample in order for it to work, I now need to:
    -   Refine it to better suit my program.
    -   Deepen my understanding of what's actually going on here. More extensive note-taking is in order.

### Next up (distant future)

-   Make the color scheme customizable via a config file passed as an additional argument.
-   Account for interleaved Phylip files. For example:

```
1 20
t1  AGCTACACGC
t2  AGC_ACAAGC
t3  AGC_ACAAGC

ACGT___AC_
ACGT___ACT
ACGT___ACT
```

