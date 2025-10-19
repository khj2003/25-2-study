#include <iostream>
#include <string>
using namespace std;

int add(int a, int b) {//int
    cout << "int: ";
    return a + b;
}

short add(short a, short b) {//short
    cout << "short: ";
    return a + b;
}

float add(float a, float b) {//float
    cout << "float: ";
    return a + b;
}

double add(double a, double b) {//double
    cout << "double: ";
    return a + b;
}

string add(string a, string b) {//string
    cout << "string: ";
    return a + b;
}

int main() {
    int i1 = 3, i2 = 5;
    short s1 = 3, s2 = 7;
    float f1 = 2.2f, f2 = 2.3f;
    double d1 = 10.1, d2 = 20.9;
    string str1 = "Kim ", str2 = "HyunJun";

    cout << add(i1, i2) << endl;
    cout << add(s1, s2) << endl;
    cout << add(f1, f2) << endl;
    cout << add(d1, d2) << endl;
    cout << add(str1, str2) << endl;

    return 0;
}