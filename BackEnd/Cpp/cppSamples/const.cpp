#include <iostream>
#include <cstring>
using namespace std;

void func(string abc) {
    cout << abc << endl;
}

const std::string str = "hello\0 world";
constexpr const char * cptr  = "hello\0 world";
int main() {
    cout << str.length() << " : " << str << endl;
    cout << strlen(cptr) << " : " << cptr << endl;
    //cout << "abc" + "abc" << endl;
    func(cptr);
}