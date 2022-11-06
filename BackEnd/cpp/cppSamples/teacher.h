#include <iostream>

class Student;
using namespace std;



class Teacher {
    friend Student;
    int age = 36;
};
