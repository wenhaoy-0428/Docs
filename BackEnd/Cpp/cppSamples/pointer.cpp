#include <iostream>
#include <typeinfo>


using namespace std;

int func(int (*a)[10]) {
    a[0][0] = 100;
    return 0;
}

int main() {
    char var[10] = {'h', 'o', '1', '8'};

    int array[10][10];

    func(array);
    cout << array[0][0]<< endl;



    return 0;
}