#include <iostream>
#include <string>
using namespace std;
//4 ���� 1��° �ڵ�
//���, �ڽ� Ŭ������ �⺻����
class Person {//�θ� Ŭ����
protected://���� ������ : protected
    string name;//��� ���� �� ��
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

};

class Student : public Person {//�ڽ�Ŭ����(���� ������: public)
private:
    string major;//�ڽ��� ��� ����

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}//�ڽ��� ������
};//������ �ʱ�ȭ ����Ʈ ���

int main() {
    Student kim("������", 23, "���Ӱ���");
}