#include <iostream>
#include <string>
using namespace std;

class Person {// 부모 클래스
protected://멤버 변수/함수를 protected로 사용 --> 자식은 접근 가능
    string name;
    int age;

    void introduce() {
        cout << "이름: " << name << ", 나이: " << age << endl;
    }

public:
    Person(string n, int a) : name(n), age(a) {}
};

class Student : public Person {// 자식 클래스
private:
    string major;

public:
    Student(string n, int a, string m) : Person(n, a), major(m) {}

    void study() {
        cout << name << " 학생이 " << major << " 전공을 공부중입니다." << endl;
    }
    void useIntroduce() { introduce(); }//부모 클래스의 함수를 가져와 사용
};//protected 접근 지정자는 자식이 접근할 수 있기 때문

int main() {
    Student kim("김현준", 23, "게임공학");
    kim.useIntroduce();   // 부모 클래스 함수 사용
    kim.study();       // 자식 클래스 함수 사용
    return 0;
}