#include <iostream>
#include <cstdarg>

using namespace std;

int func(char fmt,...) {
    va_list args;
    va_start(args, fmt);

    if(fmt == 'd') {
        int i = va_arg(args, int);
        cout << "I'm an integer: " << i << endl;
    }
}

int main() {
    func('d', 428);
    return 0;
}