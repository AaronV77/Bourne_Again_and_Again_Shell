#include <iostream>
using namespace std;
int main() {
    int numbers = 0;
    int total = 0;
    for (int i = 0; i < 10; i++) {
        std::cout << i << std::endl;
        cin >> numbers;
        total += numbers;
        numbers = 0;
    }
   // cout << "Total: " << total << endl;
    
    return 0;
}
