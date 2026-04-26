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

	// get number of entries, and sequence length, from 1st line
	auto [entries, length] = phylip_size(file);

	std::vector<


	// TUI display
	using namespace ftxui;
	std::vector<Element>  hboxes;
	hboxes.reserve(entries);
	for (int i = 0; i < entries; ++i) {
		hboxes.push_back(
				hbox({
					text(left_pad(records[i][0], max_name_len)) | border,
					text(records[i][1])                         | border | flex,
				})
		);
	}

	Element document = vbox(hboxes);

	// create full-width/-height screen, limited to [LENGTH] wide
	document = document | size(WIDTH, LESS_THAN, length);
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);
	screen.Print();

	return 0;
}
