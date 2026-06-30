#include "adminlist.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

Adminlist::Adminlist() : ptr(nullptr), size(0) {}

Adminlist::~Adminlist() {
    Admin *p = ptr;
    while (p) {
        Admin *q = p->next;
        delete p;
        p = q;
    }
}

void Adminlist::add(Admin &a) {
    Admin *p = new Admin(a);
    p->next = nullptr;
    if (!ptr) {
        ptr = p;
    } else {
        Admin *q = ptr;
        while (q->next) q = q->next;
        q->next = p;
    }
    size++;
}

Admin* Adminlist::find(string no) {
    for (Admin *p = ptr; p; p = p->next) {
        if (p->no == no) return p;
    }
    return nullptr;
}

bool Adminlist::login(string no, string pass) {
    for (Admin *p = ptr; p; p = p->next) {
        if (p->no == no && p->getpass() == pass) return true;
    }
    return false;
}

void Adminlist::remove(string no) {
    if (!ptr) return;
    if (ptr->no == no) {
        Admin *t = ptr;
        ptr = ptr->next;
        delete t;
        size--;
        return;
    }
    for (Admin *p = ptr; p->next; p = p->next) {
        if (p->next->no == no) {
            Admin *t = p->next;
            p->next = t->next;
            delete t;
            size--;
            return;
        }
    }
}

void Adminlist::write() {
    ofstream out("admins.txt");
    for (Admin *p = ptr; p; p = p->next) {
        out << p->no << "  " << p->name << "  " << p->getpass() << endl;
    }
    out.close();
}

// 修改指定管理员的密码
bool Adminlist::changePassword(string no, string newPwd) {
    Admin *p = find(no);
    if (!p) return false;
    if (newPwd.empty()) return false;
    p->setpass(newPwd);
    write();
    return true;
}

// 列出所有管理员
void Adminlist::displayAll() {
    if (!ptr) {
        cout << "（暂无管理员账号）" << endl;
        return;
    }
    cout << left;
    cout << setw(10) << "账号" << setw(15) << "姓名" << endl;
    cout << string(25, '-') << endl;
    for (Admin *p = ptr; p; p = p->next) {
        cout << setw(10) << p->no << setw(15) << p->name << endl;
    }
    cout << string(25, '-') << endl;
    cout << "共 " << size << " 个管理员" << endl;
}

bool Adminlist::loadfile() {
    ifstream in("admins.txt");
    if (!in) return false;
    string no, name, pass;
    while (in >> no >> name >> pass) {
        Admin a(no, name, pass);
        add(a);
    }
    in.close();
    return true;
}
