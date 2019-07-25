#include "create_tags5_without_guesser.h"

std::vector<std::string> create_tag5(std::string &tag){
	if(tag.empty())return std::vector<std::string>();

	//cas = ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']
    static std::unordered_set<std::string> cas({"nom", "gen", "dat", "acc", "inst", "loc", "voc"});
    //nmb = ['sg', 'pl']
    //static std::unordered_set<std::string> nmb({"sg", "pl"});
    //gnd = ['m1', 'm2', 'm3', 'f', 'n']
    static std::unordered_set<std::string> gnd({"m1", "m2", "m3", "f", "n"});

	std::vector<std::string> tags;
	int last_dot_pos=-1;
	int current_dot_pos;
	int last_colon_pos=-1;
	int current_colon_pos;
	std::string part;
	while( (current_colon_pos = tag.find(":", last_colon_pos+1)) != std::string::npos ){
		last_dot_pos = -1;
		part = tag.substr(last_colon_pos+1, current_colon_pos - last_colon_pos - 1);

		while( (current_dot_pos = part.find(".", last_dot_pos+1)) != std::string::npos ){
			tags.push_back(part.substr(last_dot_pos+1, current_dot_pos - last_dot_pos - 1));
			last_dot_pos = current_dot_pos;
		}
		if(last_dot_pos != part.length() - 1)
			tags.push_back(part.substr(last_dot_pos+1, part.length()-last_dot_pos-1));
		last_colon_pos = current_colon_pos;
	}

	if(last_colon_pos != tag.length()){
		last_dot_pos = -1;
		part = tag.substr(last_colon_pos+1, tag.length() - last_colon_pos - 1);

		while( (current_dot_pos = part.find(".", last_dot_pos+1)) != std::string::npos ){
			tags.push_back(part.substr(last_dot_pos+1, current_dot_pos - last_dot_pos - 1));
			last_dot_pos = current_dot_pos;
		}
		if(last_dot_pos != part.length() - 1)
			tags.push_back(part.substr(last_dot_pos+1, part.length()-last_dot_pos-1));
		last_colon_pos = current_colon_pos;
	}

	std::vector<std::string> res;

	std::string tags2 = "";
	std::string tags3 = "";

	for(std::string s : tags){
		if(s == "sg" || s == "pl" || gnd.find(s) != gnd.end()) 
			tags2 += s+":";
		else if (cas.find(s) != cas.end()) {
			tags2 += s+":";
			tags3 += s+":";
		}
	}

	if(tags2 != tags3){
		if(tags2.length() != 0){
			res.push_back(tags2.substr(0, tags2.length()-1));
		}

		if(tags3.length() != 0){
			res.push_back(tags3.substr(0, tags3.length()-1));
		}
	} else {
		if(tags2.length() != 0){
			res.push_back(tags2.substr(0, tags2.length()-1));
		}
	}

	return res;
}

//#define DEBUG

std::vector<std::string> create_tags5_without_guesser(std::vector<std::string> tags){
	#ifdef DEBUG
		for(int i=0;i<tags.size();i++)std::cout<<tags[i]<<std::endl;
	#endif
	if(std::find(tags.begin(), tags.end(), "ign") != tags.end())return std::vector<std::string>({"ign"});

	std::vector< std::vector<std::string> > res(tags.size());

	for(int i = 0;i<tags.size();i++){
		res[i] = create_tag5(tags[i]); 
	}

	std::vector<std::string> res_flatten = flatten(res);

	uniq_inplace(res_flatten);
	return res_flatten;
}