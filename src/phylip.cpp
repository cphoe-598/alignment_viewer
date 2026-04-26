#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

/*
 * Process first line of a phylip file.
 * Return (a) number of entries, (b) length of sequences
 */
std::pair<int, int> phylip_size(std::ifstream& f)
{
	// return value
	std::pair<int, int> res;

	// process file
	std::string first;
	getline(f, first);

	// get values
	std::stringstream ss(first);
	ss >> res[0] >> res[1];
	return res;
}

/*
 * Collect pairs of [ NAME, SEQUENCE ] from a Phylip file.
 */
std::vector< std::pair<std::string, std:string> > phylip_collect(const std::string file, int max_name_len)
{
	std::ifstream f(file);
	if (!f.good()) {
		std::cerr << "File (" << file << ") does not exist or can't be opened.\n";
		return 1;
	}
	
	// get number of entries, and sequence length from file
	auto [entries, length] = phylip_size(f);

	// return vector
	std::vector< std::pair<std::string, std::string> > records(entries);

	// collect pairs of (name, sequence)
	std::string line;
	if (f.is_open()) {
		for (int i = 0; i < entries; ++i) {
			std::getline(f, line);
			std::stringstream ss(line);
			ss >> records[i][0] >> records[i][1];  // assign values
			if (records[i][0].size() > max_name_len) {
				max_name_len = records[i][0].size();  // name padding
			}
		}
		f.close();
		return records;
	} else {
		std::cerr << "File (" << file << ") appears to contain zero entries.\n";
		return 1;
	}
}
