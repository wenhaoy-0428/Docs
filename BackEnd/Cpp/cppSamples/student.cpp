#include "teacher.h"


class Student {
public:
    int getTeacherAge();
};

int Student::getTeacherAge() {
    Teacher teacher;
    cout << teacher.age << endl;
    return teacher.age;
}


int main() {
    Student s;
    s.getTeacherAge();
}