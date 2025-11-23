#include <iostream>
#include <vector>
#include <algorithm> // find를 위한 헤더
using namespace std;

int main() {
    vector<int> v = { 10, 20, 30, 40, 50 };

    int target = 30;//내가 찾을 값을 30으로 설정

    auto it = find(v.begin(), v.end(), target);// find(시작 범위, 끝 범위, 찾을 값)

    if (it != v.end()) {//find로 찾지 못하면 v.end()값을 반환하는 걸 이용해 조건문 만듦
        cout << target << endl;
    }
    else {
        cout << "not found" << endl;
    }

    int target2 = 123;//찾을 값 123
    auto it2 = find(v.begin(), v.end(), target2);

    if (it2 != v.end()) {
        cout << target2 << endl;
    }
    else {
        cout <<  "not found" << endl;
    }

    return 0;
}