#include "admin.h"
#include <iostream>
using namespace std;

Admin::Admin(string no, string name, string p)
    : People(name, no), pass(p), next(nullptr) {}

string Admin::getpass() { return pass; }
void Admin::setpass(string p) { pass = p; }

void Admin::admindisplay() {
    cout << "账号：" << no << "  姓名：" << name
         << "  密码：" << pass << endl;
}
