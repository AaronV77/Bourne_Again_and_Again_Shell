#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<std::string> hello;
	std::string str = "Something Special";
	std::cout << str << std::endl;
	str.erase(str.begin()+(str.size()- 2), str.end());
	std::cout << str << std::endl;
	std::getline(std::cin,str);
	return 0;
} 
