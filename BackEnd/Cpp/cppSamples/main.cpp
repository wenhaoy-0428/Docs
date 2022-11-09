#include <iostream>
using namespace std;
extern int i;
// extern int test();
int test();


int main() {
    cout <<  i << endl;
    cout << test() << endl;

    return 0;
}