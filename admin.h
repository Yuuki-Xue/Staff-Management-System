#ifndef ADMIN_H
#define ADMIN_H

#include "people.h"

class Admin : public People {
private:
    string pass;       // 密码
public:
    Admin *next;       // 链表后继指针

    Admin(string no="null", string name="null", string p="123456");
    string getpass();
    void setpass(string p);
    void admindisplay();
};

#endif
