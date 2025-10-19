#include <iostream>
using namespace std;

class Storage {
private:
    int data[10];// 데이터를 저장할 배열
    int count;// 현재 저장된 원소 개수

public:
    Storage() : count(0) {}// 생성자에서 개수 초기화

    void push(int value) {// 데이터 넣기(배열의 끝에 데이터를 넣음
        data[count++] = value;//data[0]에 값을 넣은 후  count의 값 1 증가
    }

    void pop() {// 마지막 데이터 빼기
        if (count > 0) count--;//개수 감소
    }

    int top() {// 마지막 데이터 확인
        return data[count - 1];
    }

    int size() {// 저장 개수 확인
        return count;
    }
};

int main() {
    Storage s;

    s.push(1);
    s.push(2);
    s.push(3);

    cout << "데이터: " << s.top() << endl;
    cout << "크기: " << s.size() << endl;

    s.pop(); // 마지막 데이터 제거

    cout << "제거 후 데이터: " << s.top() << endl;
    cout << "제거 후 크기: " << s.size() << endl;

    return 0;
}