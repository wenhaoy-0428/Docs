#include <iostream>
using namespace std;

class Foo {
public:
    Foo() {
        cout << "Constructor" << endl;
        val_ = 10;
    }
    Foo(const Foo& other) {
        cout << "Copy Constructor called" << endl;
        val_ = other.val_;
    }
    Foo(Foo && other) noexcept {
        cout << "Move Constructor called" << endl;
        *this = std::move(other);
    }

    Foo & operator=(Foo &&other) noexcept {
        cout << "Move Operator called" << endl;
        val_ = other.val_;
        return *this;
    }

    int val_;
};

Foo func() {

    Foo f;
    cout << "func" << endl;
    return f;
}

int main() {
    Foo a;
    // Foo a = func();
    // cout << a.val_ <<endl;
    Foo b = a;
    // cout << b.val_ << endl;
    // Foo * inte = &func();
}