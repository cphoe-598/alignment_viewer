### 2026-07-31

-   Adapted the FTXUI [`scrollable.cpp`](https://arthursonzogni.github.io/FTXUI/examples_2component_2scrollbar_8cpp-example.html) sample to achieve a single, fixed window that scrolls up/down + left/right. 

### 2026-08-02

#### Cosmetic

-   Viewing window now displays the input alignment file basename, instead of "Alignment".
-   The default color palette is a little more palatable.
-   Scrollbars are now visible by default. However, when dragged to "zero", they will disappear--though still be functional.
-   Now working on DNA/AA color mapping (CURRENTLY BROKEN)

#### Technical

-   I noticed that in the viewing window, the alignment was thrown off if the input PHYLIP file had uneven spacing between taxa names and sequences. This was because of the way I parsed the file, and is now fixed.

