#include <vector>

#ifndef PHYLIP_H
#define PHYLIP_H


struct Phylip {
	// holds pairs of [TAXA, SEQUENCE]
	std::vector< std::pair<std::string, std::string> > entries;
	int n_taxa;   // number of taxa-sequence pairs
	int seq_len;  // length of seqeunces
};

std::pair<int, int> phylip_size(const std::string file);

struct Phylip phylip_collect(const std::string file);


#endif
