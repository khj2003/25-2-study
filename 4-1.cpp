#include <iostream>
#include <string>
using namespace std;

class Person {//�θ� Ŭ����
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

};

class Student : public Person {//�ڽ�Ŭ����(���� ������: public)
private:
    string major;

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}
};//������ �ʱ�ȭ ����Ʈ ���

int main() {
    Student kim("������", 23, "���Ӱ���");
}