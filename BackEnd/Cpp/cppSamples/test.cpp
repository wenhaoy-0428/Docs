#include <iostream>
#include "string"
using namespace std;

// class Base {
//     Base(const Base& other) {
//         cout << "Base copy" << endl;
//     }
// };

// class Derived : public Base {
//     Derived(const Derived& other) : Base(other) {
//         // Base(other);
//         cout << "Derived copy" << endl;
//     }
// };
// int main() {

// }

struct st{
    int value;
};

const int Foo() {
    return 10;
}

int main() {
    string ss = "abc";
    cout << ss << endl;
    auto e = Foo();
    cout << e << endl;
    e = 20;
    cout << e << endl;
}