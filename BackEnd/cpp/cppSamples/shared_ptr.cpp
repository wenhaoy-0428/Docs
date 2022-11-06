#include <iostream>
#include <memory>

using namespace std;


int main() {
    shared_ptr<int> sp1(new int(10));
    cout << "sp1 count: "<< sp1.use_count() << endl;
    shared_ptr<int> sp2(sp1);
    cout << "sp1 count: "<< sp1.use_count() << endl;
    cout << "sp2 count: "<< sp2.use_count() << endl;
    shared_ptr<int> sp3(sp1);
    cout << "sp1 count: "<< sp1.use_count() << endl;
    cout << "sp2 count: "<< sp2.use_count() << endl;
    cout << "sp3 count: "<< sp2.use_count() << endl;
}