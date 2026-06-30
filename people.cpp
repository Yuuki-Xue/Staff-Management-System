#include "people.h"
#include <iostream>
using namespace std;

People::People(string na, string n)
    : name(na), no(n), next(nullptr) {}

void People::display() {
    cout << "姓名：" << name << "  账号：" << no << endl;
}
