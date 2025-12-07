#include <iostream>
#include <memory>
#include <string>
using namespace std;
//형평성을 고려해 제출 시간 외엔 코드를 수정하지 않았습니다!!!!!!!!!!!!!!!
// ---------------------------
//  포켓몬 공통 인터페이스 (추상 클래스)
// ---------------------------
class Pokemon {
public:
    virtual ~Pokemon() {}
    virtual double atk() const = 0;       // 공격력 반환
    virtual void setAtk(double a) = 0;    // 공격력 설정
    virtual void damage(double dmg) = 0;  // 데미지 처리
    virtual bool faint() const = 0;       // 기절 여부
    virtual string type() const = 0;      // 포켓몬 타입 반환
    virtual double hp() const = 0;        // 체력 반환
};

// ---------------------------
//  기본 포켓몬 클래스 (공통 스탯)
// ---------------------------
class BasicPokemon : public Pokemon {
    double HP = 350;   // 기본 체력
    double ATK = 70;   // 기본 공격력
    string TYPE;       // 포켓몬 타입

public:
    BasicPokemon(const string& t) : TYPE(t) {}

    double atk() const override { return ATK; }
    void setAtk(double a) override { ATK = a; }

    // 피해를 입으면 체력 감소
    void damage(double dmg) override {
        HP -= dmg;
        if (HP < 0) HP = 0;
        cout << TYPE << " 타입 포켓몬이 " << dmg
            << " 피해! (남은 체력: " << HP << ")\n";
    }

    bool faint() const override { return HP <= 0; }
    string type() const override { return TYPE; }
    double hp() const override { return HP; }
};

// ---------------------------
//  버프 데코레이터 (노말 타입 전용 공격력 1.5배)
// ---------------------------
class BuffDecorator : public Pokemon {
    shared_ptr<Pokemon> p;  // 원본 포켓몬
    double mul;             // 배율

public:
    BuffDecorator(shared_ptr<Pokemon> origin, double m = 1.5)
        : p(origin), mul(m) {
    }

    // 포인터를 통해 원본 포켓몬 기능을 위임
    double atk() const override { return p->atk(); }
    void setAtk(double a) override { p->setAtk(a); }
    void damage(double dmg) override { p->damage(dmg); }
    bool faint() const override { return p->faint(); }
    string type() const override { return p->type(); }
    double hp() const override { return p->hp(); }

    // 버프 적용 시 공격력 1.5배 증가
    void apply() {
        p->setAtk(p->atk() * mul);
        cout << "노말 타입 ATK 버프 적용! 현재 공격력: "
            << p->atk() << "\n";
    }
};

// ---------------------------
//  STAB 및 타입 상성 계산 함수
// ---------------------------
double calcMultiplier(const string& atkType, const string& defType, const string& userType)
{
    double stab = (atkType == userType ? 1.5 : 1.0); // STAB(자신 타입 공격 시 보너스)
    double eff = 1.0; // 타입 상성 기본값

    // 강점 관계
    if (atkType == "fire" && defType == "grass") eff = 2.0;
    if (atkType == "grass" && defType == "water") eff = 2.0;
    if (atkType == "water" && defType == "fire") eff = 2.0;

    // 약점 관계
    if (atkType == "fire" && defType == "water") eff = 0.5;
    if (atkType == "water" && defType == "grass") eff = 0.5;
    if (atkType == "grass" && defType == "fire") eff = 0.5;

    return stab * eff; // 최종 배율 반환
}

// ---------------------------
//  메인 전투 로직
// ---------------------------
int main() {
    string t1, t2;

    cout << "1번 포켓몬 타입(normal/fire/water/grass): ";
    cin >> t1;

    cout << "2번 포켓몬 타입(normal/fire/water/grass): ";
    cin >> t2;

    // 포인터로 각 포켓몬 생성
    shared_ptr<Pokemon> p1 = make_shared<BasicPokemon>(t1);
    shared_ptr<Pokemon> p2 = make_shared<BasicPokemon>(t2);

    bool usedBuff1 = false; // 1P 버프 사용 여부
    bool usedBuff2 = false; // 2P 버프 사용 여부

    // 전투 시작 전 정보 출력
    cout << "\n[ 선택된 포켓몬 정보 ]\n";
    cout << "1P 타입: " << p1->type()
        << " | ATK: " << p1->atk()
        << " | HP: " << p1->hp() << "\n";

    cout << "2P 타입: " << p2->type()
        << " | ATK: " << p2->atk()
        << " | HP: " << p2->hp() << "\n";

    cout << "\n전투 시작!\n";

    while (true) {

        // ------------------ 1P 턴 ------------------
        int cmd;
        cout << "\n1P 기술 선택 (1: 노말 공격 / 2: 타입공격 또는 버프): ";
        cin >> cmd;

        // 노말 타입일 경우 버프 적용
        if (p1->type() == "normal" && cmd == 2 && !usedBuff1) {
            auto dec = make_shared<BuffDecorator>(p1);
            dec->apply();
            p1 = dec;
            usedBuff1 = true;
        }
        else {
            // 공격 계산
            string atkType = (cmd == 1 ? "normal" : p1->type());
            double mul = calcMultiplier(atkType, p2->type(), p1->type());
            double dmg = p1->atk() * mul;

            cout << "> 1P의 " << atkType << " 공격! (배율 ×" << mul << ")\n";
            p2->damage(dmg);
        }

        if (p2->faint()) {
            cout << "\n1P 승리!\n";
            break;
        }

        // ------------------ 2P 턴 ------------------
        cout << "\n2P 기술 선택 (1: 노말 공격 / 2: 타입공격 또는 버프): ";
        cin >> cmd;

        // 노말 타입일 경우 버프 적용
        if (p2->type() == "normal" && cmd == 2 && !usedBuff2) {
            auto dec = make_shared<BuffDecorator>(p2);
            dec->apply();
            p2 = dec;
            usedBuff2 = true;
        }
        else {
            // 공격 계산
            string atkType = (cmd == 1 ? "normal" : p2->type());
            double mul = calcMultiplier(atkType, p1->type(), p2->type());
            double dmg = p2->atk() * mul;

            cout << "> 2P의 " << atkType << " 공격! (배율 ×" << mul << ")\n";
            p1->damage(dmg);
        }

        if (p1->faint()) {
            cout << "\n2P 승리!\n";
            break;
        }

        // ------------------ 턴 종료 후 상태 출력 ------------------
        cout << "\n[ 턴 종료 상태 ]\n";
        cout << "1P(" << p1->type() << ")  ATK: " << p1->atk()
            << "  HP: " << p1->hp() << "\n";

        cout << "2P(" << p2->type() << ")  ATK: " << p2->atk()
            << "  HP: " << p2->hp() << "\n";
    }

    cout << "\n전투 종료!\n";
    return 0;

}
