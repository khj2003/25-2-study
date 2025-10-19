#include <iostream>
#include "add.h"//add.h 파일을 가져 옴(헤더 파일) == 함수 선언과 똑같은 효과
//오브젝트 파일(소스파일)을 묶어서 실행파일을 만드는 게 링커 과정
using namespace std;

//int add(int,int);// 컴파일러는 입력 파라미터의 자료형과 개수만 고려

int main() {
	int x = 5;
	int y = 10;
	cout << add(x, y) << endl;//컴파일러는 이 줄의 함수가 템플릿인지 구분 X
}//sum.cpp의 함수 정의를 add.h 헤더파일에 넣으면 오류 X

//함수 파일을 만드는 것보단 헤더파일에 함수의 정의도 다 넣자