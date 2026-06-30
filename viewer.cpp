#include "viewer.h"
#include <iostream>
using namespace std;

Viewer::Viewer(string no, string name, string p)
    : People(name, no), pass(p), next(nullptr) {}

string Viewer::getpass() { return pass; }

void Viewer::setpass(string p) { pass = p; }

void Viewer::viewerdisplay() {
    cout << "账号：" << no << "  姓名：" << name << endl;
}
