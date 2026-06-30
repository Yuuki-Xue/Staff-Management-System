#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

#include "employee.h"
#include <string>
using namespace std;

class Employeelist {
public:
    Employee *ptr;
    int size;

    Employeelist();
    ~Employeelist();

    void add(Employee &e);
    Employee* find(string id);
    void remove(string id);
    bool update(string id, Employee &e);

    void write();
    bool loadfile();

    void display();
    void search(string field, string value, bool exact);
    void sort(string field);
    void stats(string field);

    Employee input(bool ask_id, const Employee* def = nullptr);

    // 员工自助登录
    Employee* login(string id, string password);             // 员工登录验证
    void displaySelf(string id);                             // 显示个人信息
    void displaySalary(string id);                           // 显示薪资信息
    void displayManager(string id);                          // 显示直属上级
    bool changePassword(string id, string newPwd);          // 修改本人密码
};

#endif
