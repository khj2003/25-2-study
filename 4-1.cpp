#include <iostream>
#include <string>
using namespace std;

class Person {//부모 클래스
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

};

class Student : public Person {//자식클래스(접근 지정자: public)
private:
    string major;

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}
};//생성자 초기화 리스트 사용

int main() {
    Student kim("김현준", 23, "게임공학");
}