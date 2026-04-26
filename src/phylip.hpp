#include <vector>

#ifndef PHYLIP_H
#define PHYLIP_H

std::pair<int, int> phylip_size(const std::string file);

std::vector< std::pair<std::string, std::string> > phylip_collect(const std::string file, int max_name_len, const int taxa, const int length);

#endif
