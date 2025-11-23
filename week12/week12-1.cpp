#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_vec(const vector<int>& v) {//상수 참조, 함수 안에서 값 변경 X
    for (int element : v) {//vector의 각 요소들을 element에 저장 + 반복
        cout << element << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data;
    cout << "size: " << data.size() << endl;//실제 저장된 데이터 개수
    cout << "capacity: " << data.capacity() << endl;//내부 배열에 확보된 공간 크기

    data.push_back(30);//배열의 뒤쪽으로 요소에 값을 채움
    data.push_back(20);
    data.push_back(10);

    cout << "size: " << data.size() << endl;
    cout << "capacity: " << data.capacity() << endl;
    data.pop_back();//마지막 요소 제거(공간은 줄이지 않음)
    cout << "size: " << data.size() << endl;
    cout << "capacity: " << data.capacity() << endl;

    cout << "print_vec: ";
    print_vec(data);//현재 벡터의 값들 출력
}