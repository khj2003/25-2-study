#include <iostream>
#include <string>
using namespace std;
//4 주차 1번째 코드
//상속, 자식 클래스의 기본형태
class Person {//부모 클래스
protected://접근 지정자 : protected
    string name;//멤버 변수 두 개
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

};

class Student : public Person {//자식클래스(접근 지정자: public)
private:
    string major;//자식의 멤버 변수

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}//자식의 생성자
};//생성자 초기화 리스트 사용

int main() {
    Student kim("김현준", 23, "게임공학");
}