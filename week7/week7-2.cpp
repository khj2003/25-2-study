#include <iostream>
using namespace std;

int main() {
    int* arr1 = new int[50];// ù ��° ���� �޸� �Ҵ� (50��)

    for (int i = 0; i < 50; i++) {// 50���� 1���� ���� ���� (1��° ��ҿ� 50�� ��)
        arr1[i] = 50 - i;
    }

    cout << "[ù ��° �迭]" << endl;
    for (int i = 0; i < 50; i++) {
        cout << i + 1  << ": " << arr1[i] << " ";
    }
    cout << endl << endl;

    int* arr2 = new int[100];// �� ��° ���� �޸� �Ҵ� (100��)

    for (int i = 0; i < 50; i++) {// �� 50ĭ(0~49): 50���� 1���� ���� ����
        arr2[i] = 50 - i;
    }

    for (int i = 50; i < 100; i++) {// �� 50ĭ(50~99): 50���� 99���� ����
        arr2[i] = i;
    }

    cout << "[�� ��° �迭]" << endl;
    for (int i = 0; i < 100; i++) {
        cout << i + 1 << ": " << arr2[i] << " ";
    }
    cout << endl;

    delete[] arr1;// �޸� ����
    delete[] arr2;

    return 0;
}