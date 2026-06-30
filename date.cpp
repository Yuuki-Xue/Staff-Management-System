#include "date.h"
using namespace std;

Date::Date() : year(1900), month(1), day(1) {}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

bool Date::isleap(int y) {
    return (y%4==0 && y%100!=0) || (y%400==0);
}

bool Date::check() {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isleap(year)) d[1] = 29;
    if (day < 1 || day > d[month-1]) return false;
    return true;
}

string Date::tostring() {
    string ys = to_string(year);
    while ((int)ys.size() < 4) ys = "0" + ys;
    string ms = to_string(month);
    while ((int)ms.size() < 2) ms = "0" + ms;
    string ds = to_string(day);
    while ((int)ds.size() < 2) ds = "0" + ds;
    return ys + "-" + ms + "-" + ds;
}

bool Date::parse(string s) {
    if (s.size() != 10) return false;
    if (s[4] != '-' || s[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (s[i] < '0' || s[i] > '9') return false;
    }
    year  = stoi(s.substr(0, 4));
    month = stoi(s.substr(5, 2));
    day   = stoi(s.substr(8, 2));
    return check();
}
