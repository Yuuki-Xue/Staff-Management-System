#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "date.h"
#include "people.h"
#include <string>
using namespace std;

class Employee : public People {
public:
    // 继承自 People：name（姓名）、no（员工编号）

    // 基本信息
    Date birthday;        // 生日
    string education;     // 学历
    string ethnicity;     // 民族
    string major;         // 专业
    string title;         // 职称
    string department;    // 部门
    string position;      // 职务

    // 员工自助登录（5 字段）
    string password;      // 员工登录密码（默认 123456）
    int    salary;        // 月薪（元）
    int    hire_year;     // 入职年份
    int    bonus;         // 绩效奖金（元）
    string manager_id;    // 直属上级员工编号（顶级领导留空）

    Employee *next;       // 屏蔽基类的 People *next，类型更具体

    Employee();

    string tofile();
    bool parse(string s);
};

#endif
