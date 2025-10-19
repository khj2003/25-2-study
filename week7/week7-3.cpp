#include <iostream>
using namespace std;

class Storage {
private:
    int data[10];// �����͸� ������ �迭
    int count;// ���� ����� ���� ����

public:
    Storage() : count(0) {}// �����ڿ��� ���� �ʱ�ȭ

    void push(int value) {// ������ �ֱ�(�迭�� ���� �����͸� ����
        data[count++] = value;//data[0]�� ���� ���� ��  count�� �� 1 ����
    }

    void pop() {// ������ ������ ����
        if (count > 0) count--;//���� ����
    }

    int top() {// ������ ������ Ȯ��
        return data[count - 1];
    }

    int size() {// ���� ���� Ȯ��
        return count;
    }
};

int main() {
    Storage s;

    s.push(1);
    s.push(2);
    s.push(3);

    cout << "������: " << s.top() << endl;
    cout << "ũ��: " << s.size() << endl;

    s.pop(); // ������ ������ ����

    cout << "���� �� ������: " << s.top() << endl;
    cout << "���� �� ũ��: " << s.size() << endl;

    return 0;
}