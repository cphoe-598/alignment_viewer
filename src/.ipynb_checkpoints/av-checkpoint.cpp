#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
	int entries, seq_len;
	std::ifstream f(file);
	if (f.good()) {
		std::string first;
		getline(f, first);
		std::stringstream ss(first);
		ss >> entries >> seq_len;
	} else {
		std::cerr << "File (" << file << ") does not exist or can't be opened.\n";
		return 1;
	}

	// collect tuples of (name, sequence)
	std::vector< std::array<std::string, 2> > records(entries);
	std::string line;
	int max_name_len = 10;
	if (f.is_open()) {
		for (int i = 0; i < entries; ++i) {
			std::getline(f, line);
			std::stringstream ss(line);
			ss >> records[i][0] >> records[i][1];  // assign values
			if (records[i][0].size() > max_name_len) {
				max_name_len = records[i][0].size();  // for name padding
			}
		}
		f.close();
	} else {
		std::cerr << "File (" << file << ") appears to contain zero entries.\n";
		return 1;
	}

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
	
	// create full-width/-height screen, limited to 80 wide
	document = document | size(WIDTH, LESS_THAN, 80);
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);

	// Print the screen to the console.
	screen.Print();

	return 0;
}

