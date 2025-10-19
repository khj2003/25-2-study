#include <iostream>
#include <string>
using namespace std;

template <class T>
class Storage {
private:
    T data[100]; // 데이터를 저장할 배열
    int count;   // 현재 저장된 원소 개수

public:
    Storage() : count(0) {} // 기본 생성자

    void Push(T newData) {// 데이터 추가
        data[count++] = newData;
    }

    void Pop() {// 마지막 데이터 제거
        if (count > 0)
            count--;
    }

    T GetData() {// 마지막 데이터 반환
        if (count > 0)
            return data[count - 1];
    }

    int Size() {// 현재 저장된 데이터 개수 반환
        return count;
    }
};

int main() {
    Storage<int> s1;// int형 스토리지
    s1.Push(100);
    s1.Push(200);
    cout << s1.GetData() << endl; // 200 출력

    s1.Pop();
    cout << s1.GetData() << endl; // 100 출력
    cout << "현재 크기: " << s1.Size() << endl;

    Storage<string> s2;// string형 스토리지
    s2.Push("Kim");
    s2.Push("HyunJun");

    cout << s2.GetData() << endl; // HyunJun 출력
    s2.Pop();
    cout << s2.GetData() << endl; // Kim 출력

    return 0;
}