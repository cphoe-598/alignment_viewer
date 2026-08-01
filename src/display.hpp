#include <vector>
#include <string>
#include <map>

#include "phylip.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

#ifndef DISPLAY_H
#define DISPLAY_H


/* Take a DNA string and a vector of FTXUI colors.
 * Return a vector of FTXUI text() Elements mapped to the colors.
 */
std::vector<Element> color_dna(const std::string& dna, const std::vector<Color> palette);

/* Returns a vector of hboxes, each for one name:sequence
 * entry from the input Phylip file.
 */
Element assemble_content(const Phylip records, const std::vector<Color> palette);

/* Used to place name:sequence entries into scrollable FTXUI Component that
 * will constitute the main window of the TUI display.
 */
Component window_content(Element content);

#endif
