#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <map>

#include "common.hpp"
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
"SEQ_TYPE\t0 for DNA sequences; 1 for amino acid (default is 0)\n";

std::string SEQ_TYPE;  // defined in common.hpp

// ----------------------------------------------------------------------------
// MAIN

int main(int argc, const char *argv[])
{
	if (argc < 2 || argc > 3)
	{
		std::cerr << HELP_MESSAGE << "\n";
		return 1;
	}

	// get alignment filename
	const char* file = argv[1];

	// get argument for color coding for either DNA or AA sequences
	std::string SEQ_TYPE = "dna";  
	if (argc > 2)
	{
		switch(int(argv[2]))
		{
			case 0:
				SEQ_TYPE = "dna";
			case 1:
				SEQ_TYPE = "aa";
			default:
				throw std::runtime_error("Specify sequence type with either 0 (DNA) or 1 (AA).\n");
		}
	}

	// collect records from file
	Phylip records = phylip_collect(file);

	// handle bad input
	if (records.n_taxa == 0)
	{
		throw std::runtime_error("File contained zero entries, or could not be parsed.\n");
	}

	// ---------------------------------------------
	// TUI display

	// place alignment name:sequence pairs into FTXUI vbox
	Element content = assemble_content(records, SEQ_TYPE);
	
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

