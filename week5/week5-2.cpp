#include <iostream>
using namespace std;

class Parent {
public:
	Parent() { cout << "Parent 생성자" << endl; }
	virtual ~Parent() { cout << "Parent 소멸자" << endl; }
};// Parent의 소멸자가 Child, TestChild의 소멸자와 연계가 필요(virtual)

class Child :public Parent {
public:
	Child() { cout << "Child 생성자" << endl; }
	~Child() { cout << "Child 소멸자" << endl; }
};

class TestChild : public Child {
public:
	TestChild() { cout << "TestChild 생성자" << endl; }
	~TestChild() { cout << "TestChild 소멸자" << endl; }
};

int main() {
	Parent* a = new TestChild;// TestChild 객체 동적 할당
	// Parent 타입의 클래스 포인터 --> 그래서 부모, 자식, 테스트 순으로 생성자 호출
	delete a;// Parent 타입의 포인터 해체
	//실제 메모리엔 테스트 객체가 있음, 부모 클래스의 소멸자만 호출
	cout << endl;

	Child b;//아래 두 객체는 부모의 생성자부터 호출된 후
	cout << endl;
	TestChild c;//역순으로 소멸자 호출됨
}