#include <vector>
#include <map>
#include <unordered_map>
#include <string>

std::vector< std::vector< std::vector< int > > > pad(std::vector< std::vector< std::vector< std::string > > > batch, std::map<std::string, int> features_dict);
std::vector< std::vector< std::vector< int > > > pad2(std::vector< std::vector< std::vector< std::string > > > batch);
std::vector<int> k_hot(std::vector<std::string> s, std::map<std::string, int> features_dict);
std::vector<int> k_hot2(std::vector<std::string> s);
