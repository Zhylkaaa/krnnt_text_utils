#include "pad.h"

std::vector< std::vector< int > > pad(std::vector< std::vector< std::string > > batch, std::map<std::string, int> unique_features_dict) {
	std::vector< std::vector< int > > result(batch.size(), std::vector<int>(unique_features_dict.size(), 0));

	for(int i = 0;i<batch.size();i++){
		for(int j = 0;j<batch[i].size();j++){
			result[i][unique_features_dict[batch[i][j]]] = 1;
		}
	}

	return result;
}