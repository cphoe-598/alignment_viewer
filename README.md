# alignment_viewer

A sequence alignment viewer for me to practice C++. This program generates a TUI powered by [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

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

## To do

### Last time

Changed the way it parses the Phylip file. Any taxa name length should now work.

### Next time

-   Combine sequences so they display in a single box.
-   Map background colors to nucleotides.

### In the distant future

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

