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

## Progress

### Last time

-   Entries/sequences are no longer displayed in their own big, clunky boxes. They're now just line-after-line, if that makes sense.
-   Nucleotides are now mapped to colors. The color scheme I chose isn't great.

### Next up (near future)

-   Adapt the [`scrollable.cpp` FTXUI sample project](https://arthursonzogni.github.io/FTXUI/examples_2component_2scrollbar_8cpp-example.html) to achieve a single, fixed window that scrolls up/down + left/right.

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

