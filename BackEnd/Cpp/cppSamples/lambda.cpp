#include <iostream>
using namespace std;

// int main() {
//     int val_ = 20;
//     auto lambda = [&val_]() mutable -> void {
//         cout << "lambda1: " << val_ << endl;
//         val_ = 40;
//         cout << "lambda2: " << val_ << endl;
//     };
//     val_ = 50;
//     cout << val_ << endl;
//     lambda();
//     cout << val_ << endl;

// }

int main() {
    int val_ = 20;
    auto lambda = [val_]() -> void {
        cout << "lambda1: " << val_ << endl;
    };
    val_ = 30;
    cout << val_ << endl;
    lambda();
    cout << val_ << endl;
}

