#include "pad.h"

std::map<std::string, int> unique_features_dict;

std::vector< std::vector< std::vector< int > > > pad(std::vector< std::vector< std::vector< std::string > > > batch, std::map<std::string, int> features_dict) {
	unique_features_dict = features_dict;
	std::vector< std::vector< std::vector< int > > > result(batch.size());
	size_t dict_size = unique_features_dict.size();
	std::map<std::string,int>::iterator it;

	for(int i = 0;i<batch.size();i++){
		result[i] = std::vector< std::vector< int > >(batch[i].size(), std::vector<int>(dict_size, 0));
		for(int j = 0;j<batch[i].size();j++){
			for(int k = 0;k<batch[i][j].size();k++){
				it = unique_features_dict.find(batch[i][j][k]);
				if(it != unique_features_dict.end()){
					result[i][j][it->second] = 1;
				}
			}
		}
	}

	return result;
}


std::vector< std::vector< std::vector< int > > > pad2(std::vector< std::vector< std::vector< std::string > > > batch) {
	std::vector< std::vector< std::vector< int > > > result(batch.size());
	size_t dict_size = unique_features_dict.size();
	std::map<std::string,int>::iterator it;

	for(int i = 0;i<batch.size();i++){
		result[i] = std::vector< std::vector< int > >(batch[i].size(), std::vector<int>(dict_size, 0));
		for(int j = 0;j<batch[i].size();j++){
			for(int k = 0;k<batch[i][j].size();k++){
				it = unique_features_dict.find(batch[i][j][k]);
				if(it != unique_features_dict.end()){
					result[i][j][it->second] = 1;
				}
			}
		}
	}

	return result;
}