#include "uniq.h"

std::vector<std::string> uniq(std::vector< std::string > inp){
	std::unordered_set<std::string> seen;
	std::vector<std::string> res; 
	seen.rehash(2*inp.size());

	for(int i = 0;i<inp.size();i++){
		if(seen.find(inp[i]) == seen.end()){
			res.push_back(inp[i]);
			seen.insert(inp[i]);
		}
	}

	return res;
}

void uniq_inplace(std::vector< std::string > &inp){
        std::unordered_set<std::string> seen;
        seen.rehash(2*inp.size());
	size_t len = 0;

        for(int i = 0;i<inp.size();i++){
                if(seen.find(inp[i]) == seen.end()){
                        inp[len++] = inp[i];
			seen.insert(inp[i]);
                }
        }

        inp = std::vector<std::string>(inp.begin(), inp.begin() + len);
}
