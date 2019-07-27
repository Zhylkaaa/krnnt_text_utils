#include "pad.h"

std::vector< std::vector< std::vector< int > > > pad(std::vector< std::vector< std::vector< std::string > > > batch, std::map<std::string, int> unique_features_dict) {
	std::vector< std::vector< std::vector< int > > > result(batch.size());

	for(int i = 0;i<batch.size();i++){
		result[i] = std::vector< std::vector< int > >(batch[i].size(), std::vector<int>(unique_features_dict.size(), 0));
		for(int j = 0;j<batch[i].size();j++){
			for(int k = 0;k<batch[i][j].size();k++){
				result[i][j][unique_features_dict[batch[i][j][k]]] = 1;
			}
		}
	}

	return result;
}