#include <iostream>
using namespace std;

class Parent {//부모 클래스
public://접근 지정자 : public
    Parent() {//생성자
        cout << "부모 생성자 호출" << endl;
    }//생성자 호출 시 출력
    ~Parent() {//소멸자
        cout << "부모 소멸자 호출" << endl;
    }//소멸자 호출 시 출력
};

class Child : public Parent {//자식 클래스를 public으로 지정
public://접근 지정자 : public
    Child() {
        cout << "자식 생성자 호출" << endl;
    }
    ~Child() {
        cout << "자식 소멸자 호출" << endl;
    }
};

int main() {
    Child a;  // 생성 : 부모 -> 자식
    return 0; // 소멸 : 자식 -> 부모
}
