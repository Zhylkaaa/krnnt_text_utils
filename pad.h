#include <vector>
#include <map>
#include <unordered_map>
#include <string>

std::vector< std::vector< std::vector< int > > > pad(std::vector< std::vector< std::vector< std::string > > > batch, std::map<std::string, int> features_dict);
std::vector< std::vector< std::vector< int > > > pad2(std::vector< std::vector< std::vector< std::string > > > batch);