#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date {
public:
    int year, month, day;
    Date();
    Date(int y, int m, int d);

    bool isleap(int y);
    bool check();
    string tostring();
    bool parse(string s);
};

#endif
