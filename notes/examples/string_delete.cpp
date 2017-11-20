#include <iostream>
#include <string>
using namespace std;

int main() {
	string str = "ILoveCookies";
	//~ str.erase(str.begin()+(str.size()-1), str.end());
	//~ str.erase(1,1);
	//~ str.erase(0,0);
	str.erase(str.begin()+0);

	cout << str << endl;
	return 0;
}
