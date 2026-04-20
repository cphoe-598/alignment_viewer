# alignment_viewer

A sequence alignment viewer for me to practice C++. This program generates a TUI powered by [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

## Usage

```bash
./av [PATH_TO_ALN_FILE]
```

Program takes a path to a file in alignment format (currently only takes [Phylip format](https://en.wikipedia.org/wiki/PHYLIP)).

The program parses the file, and displays sequence identifiers and sequences to the console.

## Installation

Clone this repository, then run the crude cmake script. An executable `av` will be located in the `build` directory.

```bash
git clone https://github.com/cphoe-598/alignment_viewer.git
cd alignment_viewer
./run_cmake.sh
```

## To do

-  Combine sequences so they display in a single box.
-  Map background colors to nucleotides.
-  Add support for other alignment file types.
