#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "phylip.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

// ---------------------------------------------------------------------------
// CONSTANTS

// for mapping nucleotides to colors
std::vector<Color> PALETTE_DNA = {        // DNA
	Color(167, 35, 111, 255),  // A
	Color(245, 108, 64, 255),  // C
	Color(135, 116, 31, 255),  // G
	Color(46, 150, 153, 255),  // T
	Color(0, 0, 0, 0)          // gap
};
std::vector<Color> PALETTE_AA = {        // AMINO ACIDS
	Color(171, 0, 0, 255),  // A
	Color(171, 0, 146, 255),  // R
	Color(171, 97, 0, 255),  // D
	Color(171, 164, 0, 255),  // N
	Color(134, 171, 0, 255),  // C
	Color(73, 171, 0, 255),  // E
	Color(11, 171, 0, 255),  // Q
	Color(0, 171, 50, 255),  // G
	Color(0, 171, 112, 255),  // H
	Color(0, 161, 171, 255),  // I
	Color(0, 125, 171, 255),  // L
	Color(1, 1, 1, 255),  // K
	Color(1, 1, 1, 255),  // M
	Color(1, 1, 1, 255),  // F
	Color(1, 1, 1, 255),  // P
	Color(1, 1, 1, 255),  // S
	Color(1, 1, 1, 255),  // T
	Color(1, 1, 1, 255),  // W
	Color(1, 1, 1, 255),  // Y
	Color(1, 1, 1, 255),  // V
	Color(0, 0, 0, 0)          // gap
};


// ----------------------------------------------------------------------------

/* Take a DNA string and a vector of FTXUI colors.
 * Return a vector of FTXUI text() Elements mapped to the colors.
 */
std::vector<Element> color_dna(const std::string& dna, const std::vector<Color> palette)
{
	// return value
	std::vector<Element> multicolored;
	multicolored.reserve(dna.length());

	// map characters to colors
	std::map<char, Color> m{{'A', palette[0]}, {'C', palette[1]}, {'G', palette[2]},
				{'T', palette[3]}, {'_', palette[4]}};
	for (size_t i = 0; i < dna.length(); ++i) {
		multicolored.push_back(text(std::string{dna[i]}) | bgcolor(m[dna[i]]));
	}
	return multicolored;
}

/* Returns a vector of hboxes, each for one name:sequence
 * entry from the input Phylip file.
 */
Element assemble_content(const Phylip records)
{
	// will collect ftxui::hboxes of name:sequence pairs
	std::vector<Element> hboxes;
	hboxes.reserve(records.n_taxa);

	// indicate which color palette to use
	std::vector<Color> palette;
	if (SEQ_TYPE == "dna") {
		palette = palette_dna;
	} else {
		palette = palette_aa;
	}
	
	// get length of longest taxa name (for padding)
	int max_len = max_name_len(records);

	for (int i = 0; i < records.n_taxa; ++i) {

		auto name = records.entries[i].first;
		auto sequence = records.entries[i].second;

		// map sequence characters to FTXUI colors
		auto seq_colored = color_dna(sequence, palette);

		// juxtapose the name and sequence of each entry
		// name.push_back(' ');
		hboxes.push_back(hbox({
		    text( [name, len = name.length() - 1, max_len, sequence]()->std::string{
					return name + std::string((max_len - len), ' ');
			}() ) | bold,
		    hbox(std::move(seq_colored))
		}));
	}

	return vbox(std::move(hboxes));
}

/* Used to place name:sequence entries into scrollable FTXUI Component that
 * will constitute the main window of the TUI display.
 *
 * NOTE: This was adapted from sample code provided by FTXUI's author (see URL).
 * https://arthursonzogni.github.io/FTXUI/module-component-examples.html#scrollbar
 *
 * I just needed it to work as a baseline, as I am finding some aspects of
 * FTXUI a little confusing. In the future, I will make it better suit my use case.
 */
Component window_content(Element content) {
	class Impl : public ComponentBase {
		private:
			Element content_;
			float scroll_x = 0.f;
			float scroll_y = 0.f;
		public:
			explicit Impl(Element content) : content_(std::move(content)) {
				// create scrollable window
				auto scrollable_content = Renderer([this] {
					return content_ | focusPositionRelative(scroll_x, scroll_y) | frame | flex;
				});

				// left-right slider
				SliderOption<float> option_x;
				option_x.value          = &scroll_x;
				option_x.min            = -0.05f;
				option_x.max            = 1.f;
				option_x.increment      = 0.1f;
				option_x.direction      = Direction::Right;
				option_x.color_active   = Color::Grey100;
				option_x.color_inactive = Color::Grey50;
				auto scrollbar_x        = Slider(option_x);
				
				// up-down slider
				SliderOption<float> option_y;
				option_y.value          = &scroll_y;
				option_y.min            = -0.05f;
				option_y.max            = 1.f;
				option_y.increment      = 0.1f;
				option_y.direction      = Direction::Down;
				option_y.color_active   = Color::Grey100;
				option_y.color_inactive = Color::Grey50;
				auto scrollbar_y        = Slider(option_y);
				
				Add(Container::Vertical({
					Container::Horizontal({scrollable_content, scrollbar_y,}) | flex,
					Container::Horizontal({scrollbar_x, Renderer([] { return text(L"x"); }),}),
				}));
			}
	};
	return Make<Impl>(content);
}

