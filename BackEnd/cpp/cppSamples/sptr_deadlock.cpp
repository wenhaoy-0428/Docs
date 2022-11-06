#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Person {
    string name_;
    shared_ptr<Person> partner_;
public:
    Person(string name) {
        name_ = name;
    }
    friend bool partnerUp(shared_ptr<Person> p1, shared_ptr<Person> p2) {
        p1->partner_ = p2;
        p2->partner_ = p1;
        cout << p1->name_ << " is not partnered with " << p2->name_ << endl;
        return true;
    }
};

int main() {
    shared_ptr<Person> lucy {make_shared<Person>("lucy")};
    shared_ptr<Person> lala {make_shared<Person>("lala")};
    partnerUp(lucy, lala);
    cout << lucy.use_count() << endl; // 2 lucy -> Person(lucy) lala->partner_ = Person(lucy) --> 2
    cout << lala.use_count() << endl; // 2 same  as above.
}