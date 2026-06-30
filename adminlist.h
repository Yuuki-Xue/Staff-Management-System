#ifndef ADMINLIST_H
#define ADMINLIST_H

#include "admin.h"

class Adminlist {
public:
    Admin *ptr;
    int size;

    Adminlist();
    ~Adminlist();

    void add(Admin &a);
    Admin* find(string no);
    bool login(string no, string pass);
    void remove(string no);
    bool changePassword(string no, string newPwd);   // 修改指定管理员的密码
    void write();
    bool loadfile();
    void displayAll();                               // 列出所有管理员
};

#endif
