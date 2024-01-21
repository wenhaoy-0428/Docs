#include <iostream>
using namespace std;

class Base {
    virtual void func() {
    };
};

class Derived : public Base {

};

class Derived2 : public Derived {

};

int main() {
    Base * bp = new Derived();
    Derived * dp = dynamic_cast<Derived *>(bp); // valid
    Derived2 * dp2 = dynamic_cast<Derived2 *>(bp); // invalid
    if(dp2 == nullptr) {
        cout << "nullptr" << endl;
    } else {
        cout << "valid" << endl;
    }
}