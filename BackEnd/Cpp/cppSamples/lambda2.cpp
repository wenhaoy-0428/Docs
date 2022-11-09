#include <iostream>

void func(std::function<void(void)> lambda) {
    lambda(); // 20
}

int main() {
    int val = 20;
    auto lambda = [val]() -> void {
        cout << "lambda: " << val << endl;
    };
    val = 30;
    func(lambda);
}