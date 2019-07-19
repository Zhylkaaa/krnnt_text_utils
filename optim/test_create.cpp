#include "create_tags4_without_guesser.cpp"
#include <iostream>

int main(){

	std::string s = "depr:pl:nom:m2";
	std::vector<std::string> v(1, s);
	std::cout<<v[0]<<std::endl;
	std::vector<std::string> res = create_tags4_without_guesser(v);
	
	for(int i = 0;i<res.size();i++){
		std::cout<<res[i]<<std::endl;
	}

	return 0;
}
