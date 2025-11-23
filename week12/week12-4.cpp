#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = { 5, 3, 8, 1, 3 };

    // 1. 배열 내 값들을 뒤집음(reverse)
    reverse(v.begin(), v.end());
    cout << "reverse: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 2. 모든 값들을 하나로 채움(fill)
    fill(v.begin(), v.end(), 9);
    cout << "fill: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 3. 두 변수의 값 바꾸기(swap)
    int a = 10, b = 20;
    swap(a, b);
    cout << "swap 후: " << a << ", " << b << endl;

    // 4. 가장 큰 값 찾기(max_element)
    vector<int> v2 = { 2, 7, 4, 9, 5 };
    auto maxIt = max_element(v2.begin(), v2.end());
    cout << "최대값: " << *maxIt << endl;

    // 5. 특정 값이 몇 개인지 찾기(count)
    cout << "count:  " << count(v2.begin(), v2.end(), 7) << endl;

    return 0;
}