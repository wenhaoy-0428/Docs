#include <iostream>
using namespace std;
class Base {
public:
    void func() {
        cout << "Base" << endl;
    }
};

class Derived : public Base {
public:
    void func() {
        cout << "Derived" << endl;
    }
};

void myfunc(Base * b) {
    b->func();
}

int main() {
    Derived * d = new Derived();
    myfunc(d);
}