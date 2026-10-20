#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <map>

#include "phylip.hpp"
#include "display.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

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

	// handle bad input
	if (records.n_taxa == 0) {
		std::cout << "File contained zero entries, or could not be parsed.\n";
	}

	// ---------------------------------------------
	// TUI display

	// for mapping nucleotides to colors
	std::vector<Color> palette = {
		Color::Red, Color::BlueViolet, Color::Green, Color::HotPink, Color::Black
	};

	// place alignment name:sequence pairs into FTXUI vbox
	Element content = assemble_content(records, palette);
	
	// create window
	auto window = Window({
			.inner  = window_content(content),
			.title   = "Alignment",
			.width  = 80,
			.height = 30,
	});
	auto screen = App::Fullscreen();
	screen.Loop(window);


	/*
	// create full-width/-height screen, limited to [LENGTH] wide
	// Element document = document | size(WIDTH, LESS_THAN, (MAX_NAME_LEN + records.seq_len + 2));
	// Element document = vbox(content);
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);
	screen.Print();
	*/

	return 0;
}

