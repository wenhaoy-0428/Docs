#include <iostream>
#include <string>

using namespace std;

class Foo {
public:
    Foo() {}
    string getName() {
        return this->s_name;
    }
    static string s_getName() {
        return this->s_name;
    }
private:
    static string s_name;
    string name = "WelcomHere";
};

string Foo::s_name = "HelloWorld";

int main() {
    Foo f;

    cout << Foo::s_getName() << endl;
    cout << f.getName() << endl;
}