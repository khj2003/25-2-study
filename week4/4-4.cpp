#include <iostream>
#include <string>
using namespace std;

class Person {// �θ� Ŭ����
protected://��� ����/�Լ��� protected�� ��� --> �ڽ��� ���� ����
    string name;
    int age;

    void introduce() {
        cout << "�̸�: " << name << ", ����: " << age << endl;
    }

public:
    Person(string n, int a) : name(n), age(a) {}
};

class Student : public Person {// �ڽ� Ŭ����
private:
    string major;

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}

    void study() {
        cout << name << " �л��� " << major << " ������ �������Դϴ�." << endl;
    }
    void useIntroduce() { introduce(); }//�θ� Ŭ������ �Լ��� ������ ���
};//protected ���� �����ڴ� �ڽ��� ������ �� �ֱ� ����

int main() {
    Student kim("������", 23, "���Ӱ���");
    kim.useIntroduce();   // �θ� Ŭ���� �Լ� ���
    kim.study();       // �ڽ� Ŭ���� �Լ� ���
    return 0;
}