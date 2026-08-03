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

constexpr std::string_view HELP_MESSAGE = 
"Alignment viewer TUI\n\n"
"Usage: ./av <PHYLIP_FILE> <SEQ_TYPE>\n\n"
"SEQ_TYPE\t\"dna\" for DNA sequences; \"aa\" for AA sequences (without quotes)\n";

// setting for color coding for either DNA or AA sequences
std::string SEQ_TYPE = "dna";


// ----------------------------------------------------------------------------
// MAIN

int main(int argc, const char *argv[])
{
	if (argc < 2 || argc > 3) {
		std::cerr << HELP_MESSAGE << "\n";
		return 1;
	}

	const char* file = argv[1];

	// if specified sequence type argument
	if (argc > 2) {
		if (std::string(argv[2]) != "dna" && std::string(argv[2]) != "aa") {
			throw std::runtime_error("For sequence type, specify 'dna' or 'aa' (without quotes).\n");
		} else {
			SEQ_TYPE = argv[2];
		}
	}

	// collect records from file
	Phylip records = phylip_collect(file);

	// handle bad input
	if (records.n_taxa == 0) {
		throw std::runtime_error("File contained zero entries, or could not be parsed.\n");
	}

	// ---------------------------------------------
	// TUI display

	// place alignment name:sequence pairs into FTXUI vbox
	Element content = assemble_content(records);
	
	// create window
	auto window = Window({
			.inner  = window_content(content),
			.title  = [file]()->std::string {
				std::string base(file);
				return base.substr(base.find_last_of("/\\") + 1);
			}(),
			.width  = 80,
			.height = 30,
	});
	auto screen = App::Fullscreen();
	screen.Loop(window);

	return 0;
}

