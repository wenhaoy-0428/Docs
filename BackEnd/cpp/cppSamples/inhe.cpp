#include <iostream>
using namespace std;

class Base {
public:
    void getVal() {
        cout << "getVal" << endl;
    }
    void getVal(int a) {
        cout << " getVal(int a)" << endl;
    }
private:
    void abc() {}
};

class Derived: private Base {
public:
    void hello() {
        getVal();
    }
};


int main() {
    Derived d;
    d.hello();

}
