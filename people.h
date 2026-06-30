#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People {
public:
    string name;       // 姓名
    string no;         // 账号
    People *next;
    People(string na="null", string n="null");
    void display();
};

#endif
