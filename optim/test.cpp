#include "uniq.cpp"
#include <iostream>

int main(){
	std::vector<std::string> v;
	v.push_back("abd");
	v.push_back("asd");
	v.push_back("art");
	v.push_back("abd");
	v.push_back("qwe");
	v.push_back("art");
	v.push_back("tre");

	std::cout<<v.capacity()<<std::endl;

	uniq_inplace(v);

	std::cout<<v.capacity()<<std::endl;

	for(std::string s : v){
		std::cout<<s<<std::endl;
	}
	return 0;
}
