#include <iostream>
#include <sys/stat.h>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

constexpr std::string_view HELP_MESSAGE = "\
Usage: ./av <PHYLIP_FILE>\
";

inline bool file_exists (const std::string& filename) {
	struct stat buf;
	return (stat(filename, &buf) != 0);
}

 
int main(int argc, const char *argv[])
{
	if (argc != 2) {
		std::cerr << HELP_MESSAGE << "\n";
		return 1;
	}

	// get PHYLIP filename
	const char* file = argv[1];
	if ( !file_exists(file) ) {
		std::cerr << "Err: File " << file << " does not exist.\n";
		return 1;
	}

	return 0;

	/*
	using namespace ftxui;

	// three text elements
	Element document = hbox({
		text("left")   | border,
		text("middle") | border | flex,
		text("right")  | border,
	});

	// create full-width/-height screen, limited to 80 wide
	document = document | size(WIDTH, LESS_THAN, 80);
	auto screen = Screen::Create(
		Dimension::Full(), Dimension::Fit(document)  // W, H
	);
	Render(screen, document);

	// Print the screen to the console.
	// screen.Print();
	*/
}

