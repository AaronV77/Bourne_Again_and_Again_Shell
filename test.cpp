#include <iostream>
#include <string>
#include <stack>
#include <locale>

int main() {
	
	std::stack<std::string> mystack;
	
	for (int i=0; i<5; ++i) mystack.push("HI");

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
	 std::cout << ' ' << mystack.top();
	 mystack.pop();
	}
	std::cout << '\n';

  return 0;
}
