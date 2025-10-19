#include <iostream>
#include <string>
using namespace std;

template <class T>
class Storage {
private:
    T data[100]; // �����͸� ������ �迭
    int count;   // ���� ����� ���� ����

public:
    Storage() : count(0) {} // �⺻ ������

    void Push(T newData) {// ������ �߰�
        data[count++] = newData;
    }

    void Pop() {// ������ ������ ����
        if (count > 0)
            count--;
    }

    T GetData() {// ������ ������ ��ȯ
        if (count > 0)
            return data[count - 1];
    }

    int Size() {// ���� ����� ������ ���� ��ȯ
        return count;
    }
};

int main() {
    Storage<int> s1;// int�� ���丮��
    s1.Push(100);
    s1.Push(200);
    cout << s1.GetData() << endl; // 200 ���

    s1.Pop();
    cout << s1.GetData() << endl; // 100 ���
    cout << "���� ũ��: " << s1.Size() << endl;

    Storage<string> s2;// string�� ���丮��
    s2.Push("Kim");
    s2.Push("HyunJun");

    cout << s2.GetData() << endl; // HyunJun ���
    s2.Pop();
    cout << s2.GetData() << endl; // Kim ���

    return 0;
}