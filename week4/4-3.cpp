#include <iostream>
#include <string>
using namespace std;

class Person {// �θ� Ŭ����
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    void introduce() {
        cout << "�̸�: " << name << ", ����: " << age << endl;
    }
};

class Student : public Person {// �ڽ� Ŭ����
private:
    string major;

public:
    //Student() {} �θ� Ŭ������ �⺻ �����ڰ� �����Ƿ� �⺻ ������ ���� �Ұ�
    Student(string n, int a, string m) : Person(n, a), major(m) {}

    //Student(string n, int a, string m) : Person(n, a) {
    //    major = m; //�� ������� �ʱ�ȭ�� ��� �⺻ ���� + ������ ������ ����
    //}
    void study() {
        cout << name << " �л��� " << major << " ���� ���� ���Դϴ�." << endl;
    }
};

int main() {
    Student s("ȫ�浿", 21, "���Ӱ���");
    s.introduce();   // �θ� Ŭ���� �Լ� ���
    s.study();       // �ڽ� Ŭ���� �Լ� ���
    return 0;
}