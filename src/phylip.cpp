#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <limits>

#include "phylip.hpp"


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
Phylip phylip_collect(const std::string file)
{
	std::ifstream f(file);
	if (!f.good()) {
		throw std::runtime_error("File (" + file + ") does not exist or can't be opened.");
	}

	// get number of taxa, and length of sequences
	auto [taxa, length] = phylip_size(file);
	
	// initialize Phylip records object
	Phylip records;
	records.n_taxa  = taxa;
	records.seq_len = length;
	records.entries.resize(records.n_taxa);

	if (records.n_taxa == 0) {
		return records;
	}
	
	// collect pairs of (name, sequence)
	std::string line;
	if (f.is_open()) {
		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // skip first line
		for (int i = 0; i < records.n_taxa; ++i) {
			std::getline(f, line);
			
			std::stringstream ss(line);
			ss >> records.entries[i].first >> records.entries[i].second;

			// Sequence length is known, so just split line by substrings.
			// Note: This also ensures consistent spacing between taxa names and
			// sequences in the viewer window.
			// int seq_start = line.length() - length;
			// records.entries[i].first  = line.substr(0, seq_start);       // taxa
			// records.entries[i].second = line.substr(seq_start, length);  // sequence
		}
		f.close();
	}
	return records;
}

int max_name_len(const Phylip records)
{
	int max_len = 0;
	for (size_t i = 0; i < records.n_taxa; ++i) {
		int contender = records.entries[i].first.length();
		if (contender > max_len) {
			max_len = contender;
		}
	}
	return max_len;
}

