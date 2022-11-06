#include <iostream>

using namespace std;
void Foo(int & lv) {
    cout << lv << endl;
}

void Bar(int const & lv) {
    cout << lv << endl;
}

class Clazz {
public:
    Clazz(int& val) : val_(val) {}
    int& val_;
};

Clazz * factory(int val) {
    return new Clazz(val);
}

int main() {
    Clazz * c = factory(20);
    cout << c->val_ << endl;
    for (int i = 0; i < 32; i++) {
        int a = 20;
    }
    cout << c->val_ << endl; // undetermined.
}