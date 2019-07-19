#include "create_tags4_without_guesser.h"
#include "uniq.cpp"
#include "flatten.cpp"
#include <iostream>

std::vector<std::string> create_tag4(std::string &tag){
	if(tag.empty())return std::vector<std::string>(1, ""); // TODO: base case?

	//cas = ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']
        static std::unordered_set<std::string> cas({"nom", "gen", "dat", "acc", "inst", "loc", "voc"});
        //per = ['pri', 'sec', 'ter']
        static std::unordered_set<std::string> per({"pri", "sec", "ter"});

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
		tags.push_back(tag.substr(last_colon_pos+1, tag.length()-last_colon_pos-1));
	}
	//std::string pos = tags[0];

	std::string first;
	int index=-1;
	for(int i=1;i<tags.size();i++){
		if(cas.find(tags[i]) != cas.end() || per.find(tags[i]) != per.end()){
			first = tags[i];
			index = i;
			break;
		}
	}

	std::vector<std::string> res(2);
	if(index!=-1)
		res[0] = ( "1" + tags[0] + ":" + first );
	else
		res[0] = ( "1" + tags[0] );

	part = "2" + tags[0];
	for(int i=1;i<tags.size();i++){
		if(i != index)part+=(":" + tags[i]);
	}

	res[1] = part;

	//uniq_inplace(res);
	return res;
}

//#define DEBUG

std::vector<std::string> create_tags4_without_guesser(std::vector<std::string> tags){
	#ifdef DEBUG
		for(int i=0;i<tags.size();i++)std::cout<<tags[i]<<std::endl;
	#endif
	if(std::find(tags.begin(), tags.end(), "ign") != tags.end())return std::vector<std::string>({"ign"});

	std::vector< std::vector<std::string> > res(tags.size());

	for(int i = 0;i<tags.size();i++){
		res[i] = create_tag4(tags[i]); 
	}

	std::vector<std::string> res_flatten = flatten(res);

	uniq_inplace(res_flatten);
	return res_flatten;
}
