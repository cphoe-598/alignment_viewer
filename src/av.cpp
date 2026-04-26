#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include "phylip.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

// ----------------------------------------------------------------------------
// CONSTANTS

constexpr std::string_view HELP_MESSAGE = "\
Usage: ./av <PHYLIP_FILE>\
";

const int MAX_NAME_LEN = 10;

// ----------------------------------------------------------------------------
// FUNCTIONS

/*
 * Return padded string
 */
std::string left_pad(const std::string& s, const int size)
{
	std::string padded;
	padded.append(size - s.size(), ' ');
	padded.append(s);
	return padded;
}


// ----------------------------------------------------------------------------
// MAIN

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		std::cerr << HELP_MESSAGE << "\n";
		return 1;
	}

	const char* file = argv[1];

	// get number of taxa, and sequence length, from 1st line
	auto [taxa, length] = phylip_size(file);

	// collect phylip records
	// returns vector of pairs: [taxa, sequence]
	auto records = phylip_collect(file, MAX_NAME_LEN, taxa, length);

	// TUI display
	using namespace ftxui;
	std::vector<Element>  hboxes;
	hboxes.reserve(taxa);
	for (int i = 0; i < taxa; ++i) {
		hboxes.push_back(
				hbox({
					text(records[i].first)  | border,
					text(records[i].second) | border | flex,
				})
		);
	}

	Element document = vbox(hboxes);

	// create full-width/-height screen, limited to [LENGTH] wide
	document = document | size(WIDTH, LESS_THAN, (MAX_NAME_LEN + length + 2));
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);
	screen.Print();

	return 0;
}
