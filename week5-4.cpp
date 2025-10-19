#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Array {
private:
    T* data;// 동적 배열 포인터
    int count;// 현재 원소 개수
    int cap;// 배열의 크기

public:
    Array(int capacity) {// 생성 시 배열의 크기 설정
        data = new T[capacity];
        cap = capacity;
        count = 0;
    }

    ~Array() {
        delete[] data;
    }

    T front() { return data[0]; } // 첫 원소 반환
    T back() { return data[count - 1]; } // 마지막 원소 반환
    int size() { return count; } // 현재 원소 개수 반환
    bool empty() { return count == 0; } // 배열이 비어 있는지 여부
    int capacity() { return cap; } // 배열에 할당된 크기 반환
    T at(int idx) { return data[idx]; } // 인덱스의 값 반환

    void insert(int idx, T v) { // 인덱스에 값 저장
        data[idx] = v;
    }

    void push_back(T value) { // 배열 끝에 원소 추가
        if (count < cap)
            data[count++] = value;
    }

    void pop_back() { // 마지막 원소 제거 + 초기화
        if (count > 0) {
            data[count - 1] = T();
            count--;
        }
    }
};

int main() {
    Array<int> arr(5); // 배열 크기를 5로 지정

    // 원소 추가
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    cout << "원소 개수 = size(): " << arr.size() << endl; // 3

    // 첫번째, 마지막 원소 반환
    cout << "front(): " << arr.front() << endl; // 제일 처음 추가한 수 = 10
    cout << "back(): " << arr.back() << endl;   // 제일 마지막에 추가한 수 = 30

    // 특정 위치에 값 저장
    arr.insert(1, 99); // index 1에 99 저장 20 --> 99
    cout << "insert 후 at(1): " << arr.at(1) << endl; // 99

    // 특정 인덱스 값 접근
    cout << "at(2): " << arr.at(2) << endl; // 30

    // 현재 원소 개수
    cout << "size(): " << arr.size() << endl; // 3개

    // 비어 있는지 여부
    cout << "empty(): " << (arr.empty() ? "true" : "false") << endl; // 값이 들어있음 = false

    // 전체 크기
    cout << "capacity(): " << arr.capacity() << endl; // 5

    // 마지막 원소 제거
    arr.pop_back();
    cout << "pop_back 후 size(): " << arr.size() << endl; // 하나 줄어서 2
    cout << "pop_back 후 back(): " << arr.back() << endl; // 맨 뒤의 30이 제거됐으니 99

    return 0;
}
