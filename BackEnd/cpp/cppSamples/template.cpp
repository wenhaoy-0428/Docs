#include <iostream>
using namespace std;

template<class F>
class Executor;

typedef void(* func_ptr)(int a, int b);

template<typename R, typename... Args>
class Executor<R (Args...)> {
private:
    //using FunctionType = R(* func)(Args...);
    //FunctionType const func_;
    R (* func_)(Args...);
public:
    Executor(R(* func)(Args...)) : func_(func) {}
    R execute(Args... args) {
        return func_(args...);
    }
};

void func(int a, int b) {
    cout << a << "+" << b << endl;
}

int main() {
    //using FunctionType = void(*)(int a);
    //cout << typeid(func).name() << endl;
    // FunctionType ptr = func;
    func_ptr ptr = func;
    ptr(1, 2);

}