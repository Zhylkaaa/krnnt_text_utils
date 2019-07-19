#include "flatten.h"

std::vector<std::string> flatten(std::vector< std::vector<std::string> > input_lists) {
	std::vector< std::string > res;

	for(int i = 0;i<input_lists.size();i++){
		res.insert(res.end(), input_lists[i].begin(), input_lists[i].end());
	}

	return res;
}
