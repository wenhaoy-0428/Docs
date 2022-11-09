#include <iostream>

using namespace std;

class Foo {
public:
    Foo() = default;
    explicit Foo(int a) {
        age = a;
    }
    Foo(char i) = delete;

    int getAge() {
        return age;
    }
private:
    int age = 64;
};

void func(Foo f) {
    cout << "do nothing" << endl;
}

int main() {
    func(12);
    return 0;
}