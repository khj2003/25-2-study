#include <iostream>
using namespace std;

int main() {
    int* arr1 = new int[50];// 첫 번째 동적 메모리 할당 (50개)

    for (int i = 0; i < 50; i++) {// 50부터 1까지 값을 저장 (1번째 요소에 50이 들어감)
        arr1[i] = 50 - i;
    }

    cout << "[첫 번째 배열]" << endl;
    for (int i = 0; i < 50; i++) {
        cout << i + 1  << ": " << arr1[i] << " ";
    }
    cout << endl << endl;

    int* arr2 = new int[100];// 두 번째 동적 메모리 할당 (100개)

    for (int i = 0; i < 50; i++) {// 앞 50칸(0~49): 50부터 1까지 역순 저장
        arr2[i] = 50 - i;
    }

    for (int i = 50; i < 100; i++) {// 뒤 50칸(50~99): 50부터 99까지 저장
        arr2[i] = i;
    }

    cout << "[두 번째 배열]" << endl;
    for (int i = 0; i < 100; i++) {
        cout << i + 1 << ": " << arr2[i] << " ";
    }
    cout << endl;

    delete[] arr1;// 메모리 해제
    delete[] arr2;

    return 0;
}