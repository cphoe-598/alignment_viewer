#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <limits>

#include "phylip.hpp"

using namespace std;

/*
 * Process first line of a phylip file.
 * Return (a) number of entries, (b) length of sequences
 */
std::pair<int, int> phylip_size(const std::string file)
{
	// return value
	std::pair<int, int> res;

	// open file stream
	std::ifstream f(file);
	if (!f.good()) {
		throw std::runtime_error("File (" + file + ") does not exist or can't be opened.");
	}

	// get first line
	std::string first;
	getline(f, first);

	// get values
	std::stringstream ss(first);
	ss >> res.first >> res.second;
	return res;
}

/*
 * Collect pairs of [ NAME, SEQUENCE ] from a Phylip file.
 */
std::vector< std::pair<std::string, std::string> > phylip_collect(const std::string file, const int taxa, const int length)
{
	std::ifstream f(file);
	if (!f.good()) {
		throw std::runtime_error("File (" + file + ") does not exist or can't be opened.");
	}
	
	// return vector
	std::vector< std::pair<std::string, std::string> > records(taxa);
	
	// collect pairs of (name, sequence)
	std::string line;
	if (f.is_open()) {
		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // skip first line
		for (int i = 0; i < taxa; ++i) {
			std::getline(f, line);

			int seq_start = line.size() - length;

			records[i].first  = line.substr(0, seq_start);       // taxa
			records[i].second = line.substr(seq_start, length);  // sequence
		}
		f.close();
		return records;
	} else {
		throw std::runtime_error("File (" + file + ") appears to contain zero taxa.");
	}
}
