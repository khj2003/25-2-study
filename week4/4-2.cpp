#include <iostream>
using namespace std;

class Parent {//�θ� Ŭ����
public://���� ������ : public
    Parent() {//������
        cout << "�θ� ������ ȣ��" << endl;
    }//������ ȣ�� �� ���
    ~Parent() {//�Ҹ���
        cout << "�θ� �Ҹ��� ȣ��" << endl;
    }//�Ҹ��� ȣ�� �� ���
};

class Child : public Parent {//�ڽ� Ŭ������ public���� ����
public://���� ������ : public
    Child() {
        cout << "�ڽ� ������ ȣ��" << endl;
    }
    ~Child() {
        cout << "�ڽ� �Ҹ��� ȣ��" << endl;
    }
};

int main() {
    Child a;  // ���� : �θ� -> �ڽ�
    return 0; // �Ҹ� : �ڽ� -> �θ�
}
