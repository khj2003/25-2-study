#include <iostream>
#include <string>
using namespace std;

class Person {
	string name;
	string address;
	string tel;
public:
	Person(string n, string a, string t) : name(n), address(a), tel(t) {}
	~Person() {}

	void setTel(string t) { tel = t; }  // 전화번호 변경
	string getName() { return name; }
	string getAddress() { return address; }
	string getTel() { return tel; }
};

// 교수 클래스
class Professor : public Person {
public:
	Professor(string n, string a, string t) : Person(n, a, t) {
		cout << n << " 교수입니다. " << a << "번 교수실을 사용 중입니다." << endl;
	}
	~Professor() { cout << "고생했습니다." << endl << endl; }

	void inputTel() {
		string newtel;
		cout << "새 전화번호를 입력하세요: ";
		cin >> newtel;
		setTel(newtel);
	}
	void teach() {
		cout << getTel() << " 이 번호로 전화하면 가르쳐드릴게요." << endl << endl;
	}
};

// 테니스 선수 클래스
class TennisPlayer : public Person {
public:
	TennisPlayer(string n, string a, string t) : Person(n, a, t) {
		cout << n << " 선수입니다. " << a << "번 코트에서 경기중입니다." << endl;
	}
	~TennisPlayer() {
		cout << getTel() << " , 다음에 같이 경기해요." << endl << endl;
	}

	void inputTel() {
		string newtel;
		cout << "새 전화번호를 입력하세요: ";
		cin >> newtel;
		setTel(newtel);
	}
	void playTennis() {
		cout << "테니스 치는 중입니다." << endl << endl;
	}
};

// 사업가 클래스
class Businessman : public Person {
public:
	Businessman(string n, string a, string t) : Person(n, a, t) {
		cout << n << " 사업가입니다. " << a << "호 사무실을 사용 중입니다." << endl;
	}
	~Businessman() {
		cout << getTel() << " 이 번호로 연락을 남겨주세요." << endl << endl;
	}

	void inputTel() {
		string newtel;
		cout << "새 전화번호를 입력하세요: ";
		cin >> newtel;
		setTel(newtel);
	}
	void runBusiness() {
		cout << "회의중입니다. 방해하지 마시오." << endl << endl;
	}
};

// 메인 함수
int main() {
	Person Kim("현준", "6", "010-5181-0523");

	Professor Park("지성", "123", "010-0000-0000");
	Park.teach();

	TennisPlayer Te("니수", "5", "010-9999-9999");
	Te.inputTel();
	Te.playTennis();

	Businessman Sa("업가", "777", "010-7777-7777");
	Sa.inputTel();
	Sa.runBusiness();

	return 0;
}