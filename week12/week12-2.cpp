#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

void print_vec(const vector<int>& v, const string& label = "") {//label 문자열을 같이 출력
    if (!label.empty()) {
        cout << label << " ";
    }
    for (int element : v) {
        cout << element << " ";
    }
    cout << endl;
}

struct Student {
    int id;
    int score;
};

int main() {
    vector<Student> svec = { {1, 30}, {2, 80}, {4, 20}, {15, 80} };//4개의 Student 구조체 초기화
    svec.push_back({ 7, 100 });// 새 구조체 추가

    sort(svec.begin(), svec.end(), [](const Student& a, const Student& b) {
        return a.id > b.id; });
    //정렬 범위 svec.begin(), svec.end() vector의 처음부터 끝까지
    //id 순 내림차순 정렬

      for (auto i : svec) { 
        cout << i.id << ", " << i.score << endl; }
    }