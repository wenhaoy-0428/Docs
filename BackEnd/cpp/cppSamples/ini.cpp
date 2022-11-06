#include <iostream>
#include <vector>
using namespace std;

void func(std::initializer_list<int> ls) {
    for(auto it = ls.begin(); it < ls.end(); it++) {
        // *it = 10; error: read-only variable is not assignable
        cout << *it  << endl;
    }
}
int main() {
    func({1, 2, 3, 4});
    vector<int> * v = new vector<int>{1, 2, 3};

}