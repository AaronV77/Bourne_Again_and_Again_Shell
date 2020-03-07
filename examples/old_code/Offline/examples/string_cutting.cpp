#include <iostream>
#include <string>
using namespace std;

int main() {
    string example = "~/Documents";
    string home = "/home/valoroso";
    string new_example = home;
    new_example += example.substr(1);
    cout << "Here: " << new_example << endl;

    string example2 = "cd ~/Documents";
    string home2 = "/home/valoroso";
    string new_example2 = "";
    new_example2 += example2.substr(0,3);
    new_example2 += home2;
    new_example2 += example2.substr(4);
    cout << "Here: " << new_example2 << endl;
    return 0;
}