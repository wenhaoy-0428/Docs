#include <iostream>


using namespace std;

class Base1 {
public:
    virtual ~Base1() {
        cout << "Base1::delete" << endl;
    };
};

class Base2 {
public:
    explicit Base2(int a) : m_a(a) {
        init();
    }
    virtual void Foo() {
        cout << "Base2::Foo" << endl;
    }
    virtual ~Base2() {
        cout << "Base2::delete" << endl;
    }
protected:
    virtual void init() {
        cout << "Base2::Init" << endl;
    }
    int m_a;
};

class Derived : public Base1, public Base2 {
public:
    Derived(int a, int b) : Base2(a), m_b(b) {}
    void Foo() {
        cout << "Derived::Foo" << endl;
    }
    void func() {
        cout << " Hello funk" << endl;
    }
    ~Derived() {
        cout << "Derived::delete" << endl;
    }
protected:
    void init() {
        cout << "Derived::init" << endl;
    }
    int m_b;
};

int main() {
    Base2 *ptr = new Derived(3, 4);
    ptr->Foo();
    cout << sizeof(*ptr) << endl;
    delete ptr;
}