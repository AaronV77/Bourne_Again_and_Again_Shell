#include <string>
#include <iostream>

using namespace std;

int main() {

    string input = "";
    while(1) {
        cout << "Please enter input: ";
        getline(cin, input);
        cout << input << endl;
    }
    return 0;
}