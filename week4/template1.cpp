#include <iostream>
using namespace std;

template <typename T> // ���ø� �Լ�
T add(T a, T b) {
    return a + b;
}
//���⼭ ��Ÿ���� ���ø��� Ư��
//���뼺, Ÿ�� ������(�� Ÿ�� ���� ��� ����), �ϰ����� ����������
//(��:�� ���ø� �Լ��� �����ϸ� �ٷ� ���� �Լ��� �ٲ� �� ����)

int main() {//���� ����ϰ� ���� �ڷ����� ���� �ڵ� ���
    cout << add(5, 22) << endl;
    cout << add(5.22, 1.83) << endl;
    cout << add(23L, 183L) << endl;
    return 0;
}
