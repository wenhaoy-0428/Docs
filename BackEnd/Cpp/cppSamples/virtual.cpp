#include <iostream>

using namespace std;

class Base {
public:
    explicit Base(int a) {
        init(a);
    }
    void init(int a) {
        Foo(a);
    }
private:
    virtual void Foo(int a) = 0;
};

class Derived : public Base {
public:
    explicit Derived(int a) : Base(a) {

    }
private:
    void Foo(int a) override {}
};

class Foo {
    virtual static void function() {

    }
}

int main() {
    Base * bp = new Derived(3);
    delete bp;
}