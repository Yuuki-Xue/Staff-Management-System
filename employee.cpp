#include "employee.h"
using namespace std;

// 检查字符串每一位是否都是数字（基础方法，逐字符判断）
static bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

Employee::Employee()
    : People("null", "null"),     // 父类先构造（name 和 no 初始化为 "null"）
      password("123456"), salary(0), hire_year(2024),
      bonus(0), manager_id(""), next(nullptr) {}

// 输出 14 个字段：编号(name) + 姓名(no) + 生日 + ... + 密码 + 月薪 + 入职年份 + 绩效 + 上级
string Employee::tofile() {
    return no + "," + name + "," + birthday.tostring() + ","
           + education + "," + ethnicity + "," + major + ","
           + title + "," + department + "," + position + ","
           + password + "," + to_string(salary) + ","
           + to_string(hire_year) + "," + to_string(bonus) + ","
           + manager_id;
}

// 解析 14 个字段（最后字段 manager_id 可以为空字符串）
bool Employee::parse(string s) {
    string f[14];
    int idx = 0;
    string cur = "";
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == ',') {
            if (idx >= 14) return false;
            f[idx++] = cur;
            cur = "";
        } else {
            cur += s[i];
        }
    }
    if (idx != 13) return false;
    f[idx] = cur;
    no         = f[0];     // 继承自 People 的 no（员工编号）
    name       = f[1];     // 继承自 People 的 name（姓名）
    if (!birthday.parse(f[2])) return false;
    education  = f[3];
    ethnicity  = f[4];
    major      = f[5];
    title      = f[6];
    department = f[7];
    position   = f[8];
    password   = f[9];
    // 枚举字段校验：磁盘读出来的数据也要查一遍，防止人工编辑坏了
    if (education != "高中" && education != "大专" && education != "本科"
        && education != "硕士" && education != "博士") return false;
    if (title != "助理工程师" && title != "工程师"
        && title != "高级工程师" && title != "教授级高级工程师") return false;
    if (department != "人事部" && department != "技术部"
        && department != "后勤部" && department != "信息部") return false;
    if (position != "普通员工" && position != "工程师"
        && position != "团队领导" && position != "部门领导"
        && position != "公司领导") return false;
    // 数字字段逐位校验：不是纯数字直接判失败
    if (!isNumber(f[10]) || !isNumber(f[11]) || !isNumber(f[12])) return false;
    salary     = stoi(f[10]);
    hire_year  = stoi(f[11]);
    bonus      = stoi(f[12]);
    manager_id = f[13];
    return true;
}
