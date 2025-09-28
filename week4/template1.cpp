#include <iostream>
using namespace std;

template <typename T> // 템플릿 함수
T add(T a, T b) {
    return a + b;
}
//여기서 나타나는 템플릿의 특성
//재사용성, 타입 독립성(각 타입 별로 사용 가능), 일관성과 유지보수성
//(예:위 템플릿 함수만 수정하면 바로 뺄셈 함수로 바꿀 수 있음)

int main() {//내가 사용하고 싶은 자료형에 따라 자동 계산
    cout << add(5, 22) << endl;
    cout << add(5.22, 1.83) << endl;
    cout << add(23L, 183L) << endl;
    return 0;
}
