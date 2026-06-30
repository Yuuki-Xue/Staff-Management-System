#ifndef VIEWER_H
#define VIEWER_H

#include "people.h"

class Viewer : public People {
private:
    string pass;       // 密码
public:
    Viewer *next;       // 链表后继指针

    Viewer(string no="null", string name="null", string p="123456");
    string getpass();
    void setpass(string p);    // 设置密码（账号管理用）
    void viewerdisplay();
};

#endif
