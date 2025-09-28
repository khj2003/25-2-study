#include <iostream>
#include <string>
using namespace std;

class Person {// 부모 클래스
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    void introduce() {
        cout << "이름: " << name << ", 나이: " << age << endl;
    }
};

class Student : public Person {// 자식 클래스
private:
    string major;

public:
    //Student() {} 부모 클래스에 기본 생성자가 없으므로 기본 생성자 선언 불가
    Student(string n, int a, string m) : Person(n, a), major(m) {}

    //Student(string n, int a, string m) : Person(n, a) {
    //    major = m; //이 방식으로 초기화할 경우 기본 생성 + 대입의 과정이 생김
    //}
    void study() {
        cout << name << " 학생이 " << major << " 전공 공부 중입니다." << endl;
    }
};

int main() {
    Student s("홍길동", 21, "게임공학");
    s.introduce();   // 부모 클래스 함수 사용
    s.study();       // 자식 클래스 함수 사용
    return 0;
}