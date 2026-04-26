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

	// collect records from file
	Phylip records = phylip_collect(file);

	if (records.n_taxa == 0) {
		std::cout << "File contained zero entries, or could not be parsed.\n";
	}

	// TUI display
	using namespace ftxui;
	std::vector<Element>  hboxes;
	hboxes.reserve(records.n_taxa);
	for (int i = 0; i < records.n_taxa; ++i) {
		hboxes.push_back(
				hbox({
					text(records.entries[i].first)  | border,
					text(records.entries[i].second) | border | flex,
				})
		);
	}

	Element document = vbox(hboxes);

	// create full-width/-height screen, limited to [LENGTH] wide
	// document = document | size(WIDTH, LESS_THAN, (MAX_NAME_LEN + records.seq_len + 2));
	document = document;
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);
	screen.Print();

	return 0;
}
