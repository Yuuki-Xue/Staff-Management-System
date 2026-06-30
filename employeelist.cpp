#include "employeelist.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// 检查字符串每一位是否都是数字
static bool isAllDigits(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

Employeelist::Employeelist() : ptr(nullptr), size(0) {}

Employeelist::~Employeelist() {
    Employee *p = ptr;
    while (p) {
        Employee *q = p->next;
        delete p;
        p = q;
    }
}

static string getfield(Employee &e, string field) {
    if (field == "id" || field == "编号")         return e.no;
    if (field == "name" || field == "姓名")       return e.name;
    if (field == "birthday" || field == "生日")    return e.birthday.tostring();
    if (field == "education" || field == "学历")   return e.education;
    if (field == "ethnicity" || field == "民族")   return e.ethnicity;
    if (field == "major" || field == "专业")       return e.major;
    if (field == "title" || field == "职称")       return e.title;
    if (field == "department" || field == "部门")  return e.department;
    if (field == "position" || field == "职务")    return e.position;
    return "";
}

void Employeelist::add(Employee &e) {
    Employee *p = new Employee(e);
    p->next = nullptr;
    if (!ptr) {
        ptr = p;
    } else {
        Employee *q = ptr;
        while (q->next) q = q->next;
        q->next = p;
    }
    size++;
}

Employee* Employeelist::find(string id) {
    for (Employee *p = ptr; p; p = p->next) {
        if (p->no == id) return p;
    }
    return nullptr;
}

void Employeelist::remove(string id) {
    if (!ptr) return;
    if (ptr->no == id) {
        Employee *t = ptr;
        ptr = ptr->next;
        delete t;
        size--;
        return;
    }
    for (Employee *p = ptr; p->next; p = p->next) {
        if (p->next->no == id) {
            Employee *t = p->next;
            p->next = t->next;
            delete t;
            size--;
            return;
        }
    }
}

bool Employeelist::update(string id, Employee &e) {
    Employee *p = find(id);
    if (!p) return false;
    *p = e;
    p->no = id;
    return true;
}

void Employeelist::write() {
    ofstream out("employees.txt");
    for (Employee *p = ptr; p; p = p->next) {
        out << p->tofile() << endl;
    }
    out.close();
}

bool Employeelist::loadfile() {
    ifstream in("employees.txt");
    if (!in) return false;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        Employee e;
        if (e.parse(line)) {
            add(e);
        }
    }
    in.close();
    return true;
}

void Employeelist::display() {
    if (!ptr) {
        cout << "（暂无员工记录）" << endl;
        return;
    }
    cout << left;
    cout << setw(8)  << "编号" << setw(10) << "姓名"
         << setw(12) << "生日" << setw(8) << "学历"
         << setw(8)  << "民族" << setw(12) << "专业"
         << setw(15) << "职称" << setw(10) << "部门"
         << setw(12) << "职务" << endl;
    cout << string(95, '-') << endl;
    for (Employee *p = ptr; p; p = p->next) {
        cout << setw(8)  << p->no
             << setw(10) << p->name
             << setw(12) << p->birthday.tostring()
             << setw(8)  << p->education
             << setw(8)  << p->ethnicity
             << setw(12) << p->major
             << setw(15) << p->title
             << setw(10) << p->department
             << setw(12) << p->position << endl;
    }
    cout << string(95, '-') << endl;
    cout << "总记录数：" << size << " 条" << endl;
}

void Employeelist::search(string field, string value, bool exact) {
    if (!ptr) {
        cout << "（无员工数据可查）" << endl;
        return;
    }
    if (getfield(*ptr, field) == "") {
        cout << "（不支持的字段：" << field << "）" << endl;
        return;
    }
    int found = 0;
    cout << "查询结果：" << endl;
    for (Employee *p = ptr; p; p = p->next) {
        string fv = getfield(*p, field);
        bool match = exact
            ? (fv == value)
            : (fv.find(value) != string::npos);
        if (match) {
            cout << "  " << p->no << "  " << p->name
                 << "  " << p->birthday.tostring()
                 << "  " << p->department << endl;
            found++;
        }
    }
    if (found == 0) {
        cout << "（无匹配记录）" << endl;
    } else {
        cout << "共找到 " << found << " 条" << endl;
    }
}

static void swap_emp_data(Employee &a, Employee &b) {
    Employee tmp = a;
    a.no         = b.no;
    a.name       = b.name;
    a.birthday   = b.birthday;
    a.education  = b.education;
    a.ethnicity  = b.ethnicity;
    a.major      = b.major;
    a.title      = b.title;
    a.department = b.department;
    a.position   = b.position;

    b.no         = tmp.no;
    b.name       = tmp.name;
    b.birthday   = tmp.birthday;
    b.education  = tmp.education;
    b.ethnicity  = tmp.ethnicity;
    b.major      = tmp.major;
    b.title      = tmp.title;
    b.department = tmp.department;
    b.position   = tmp.position;
    // 注意：a.next 和 b.next 不参与交换
}

void Employeelist::sort(string field) {
    if (!ptr || !ptr->next) return;
    for (Employee *i = ptr; i && i->next; i = i->next) {
        for (Employee *j = ptr; j->next; j = j->next) {
            string a = getfield(*j, field);
            string b = getfield(*j->next, field);
            if (a.empty() || b.empty()) {
                cout << "（不支持的字段：" << field << "）" << endl;
                return;
            }
            if (a > b) {
                swap_emp_data(*j, *j->next);
            }
        }
    }
    cout << "已按 [" << field << "] 升序排序。" << endl;
}

void Employeelist::stats(string field) {
    string values[200];
    int counts[200];
    int n = 0;
    for (Employee *p = ptr; p; p = p->next) {
        string fv = getfield(*p, field);
        if (fv.empty()) {
            cout << "（不支持的字段：" << field << "）" << endl;
            return;
        }
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (values[i] == fv) { idx = i; break; }
        }
        if (idx == -1) {
            values[n] = fv;
            counts[n] = 1;
            n++;
        } else {
            counts[idx]++;
        }
    }
    cout << "按 [" << field << "] 统计：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << values[i] << "：" << counts[i] << " 人" << endl;
    }
}

Employee Employeelist::input(bool ask_id, const Employee* def) {
    Employee e;
    string line;
    // 如果传入了 def（修改模式），用它预填字段；空输入则保留原值
    if (def) e = *def;

    // 1. 编号：必填 + 必须全数字；新增时还要查重（重复编号立即报错，不继续录入）
    if (ask_id) {
        while (true) {
            cout << "编号（必填，数字）："; cin >> e.no;
            if (e.no.empty()) { cout << "（编号不能为空）" << endl; continue; }
            if (!isAllDigits(e.no)) { cout << "（编号必须是数字）" << endl; continue; }
            // 查重：编号已存在则立即报错并返回特殊标记
            if (find(e.no)) {
                cout << "[失败] 编号 " << e.no << " 已存在，请勿重复添加。" << endl;
                e.no = "";   // 用空串作为"用户取消"标记
                return e;
            }
            break;
        }
    }

    // 2. 姓名：必填；修改模式下空输入保留原值
    while (true) {
        cout << "姓名" << (def ? "[" + e.name + "]" : "") << "：";
        cin >> line;
        if (line.empty() && def) { /* 保留 e.name */ break; }
        if (!line.empty()) { e.name = line; break; }
        cout << "（姓名不能为空）" << endl;
    }

    // 3. 生日：必须合法；修改模式下空输入保留原值
    while (true) {
        cout << "生日" << (def ? "[" + e.birthday.tostring() + "]" : "") << "（YYYY-MM-DD）：";
        cin >> line;
        if (line.empty() && def) break;  // 保留原值
        if (e.birthday.parse(line)) break;
        cout << "（日期格式或值不合法）" << endl;
    }

    // 4. 学历：5 选 1；修改模式下空输入保留原值
    while (true) {
        cout << "学历" << (def ? "[" + e.education + "]" : "") << "（高中/大专/本科/硕士/博士）：";
        cin >> line;
        if (line.empty() && def) break;
        if (line == "高中" || line == "大专" || line == "本科"
            || line == "硕士" || line == "博士") { e.education = line; break; }
        cout << "（学历必须是 高中/大专/本科/硕士/博士 之一）" << endl;
    }

    // 5. 民族：必填（无枚举限制）；修改模式下空输入保留原值
    while (true) {
        cout << "民族" << (def ? "[" + e.ethnicity + "]" : "") << "：";
        cin >> line;
        if (line.empty() && def) break;
        if (!line.empty()) { e.ethnicity = line; break; }
        cout << "（民族不能为空）" << endl;
    }

    // 6. 专业：必填（无枚举限制）；修改模式下空输入保留原值
    while (true) {
        cout << "专业" << (def ? "[" + e.major + "]" : "") << "：";
        cin >> line;
        if (line.empty() && def) break;
        if (!line.empty()) { e.major = line; break; }
        cout << "（专业不能为空）" << endl;
    }

    // 7. 职称：4 选 1；修改模式下空输入保留原值
    while (true) {
        cout << "职称" << (def ? "[" + e.title + "]" : "") << "（助理工程师/工程师/高级工程师/教授级高级工程师）：";
        cin >> line;
        if (line.empty() && def) break;
        if (line == "助理工程师" || line == "工程师"
            || line == "高级工程师" || line == "教授级高级工程师") { e.title = line; break; }
        cout << "（职称必须是 助理工程师/工程师/高级工程师/教授级高级工程师 之一）" << endl;
    }

    // 8. 部门：4 选 1；修改模式下空输入保留原值
    while (true) {
        cout << "部门" << (def ? "[" + e.department + "]" : "") << "（人事部/技术部/后勤部/信息部）：";
        cin >> line;
        if (line.empty() && def) break;
        if (line == "人事部" || line == "技术部"
            || line == "后勤部" || line == "信息部") { e.department = line; break; }
        cout << "（部门必须是 人事部/技术部/后勤部/信息部 之一）" << endl;
    }

    // 9. 职务：5 选 1；修改模式下空输入保留原值
    while (true) {
        cout << "职务" << (def ? "[" + e.position + "]" : "") << "（普通员工/工程师/团队领导/部门领导/公司领导）：";
        cin >> line;
        if (line.empty() && def) break;
        if (line == "普通员工" || line == "工程师"
            || line == "团队领导" || line == "部门领导"
            || line == "公司领导") { e.position = line; break; }
        cout << "（职务必须是 普通员工/工程师/团队领导/部门领导/公司领导 之一）" << endl;
    }

    // 10. 密码：默认 123456；修改模式下空输入保留原值
    cout << "登录密码" << (def ? "[" + e.password + "]" : "") << "（默认 123456）：";
    cin >> line;
    if (!line.empty()) e.password = line;
    if (e.password.empty()) e.password = "123456";

    // 11. 月薪：必须是数字；修改模式下空输入保留原值
    while (true) {
        cout << "月薪" << (def ? "[" + to_string(e.salary) + "]" : "") << "（元）：";
        cin >> line;
        if (line.empty() && def) break;
        if (isAllDigits(line)) { e.salary = stoi(line); break; }
        cout << "（月薪必须是数字）" << endl;
    }

    // 12. 入职年份：必须是 4 位数字，且不能晚于 2026；修改模式下空输入保留原值
    while (true) {
        cout << "入职年份" << (def ? "[" + to_string(e.hire_year) + "]" : "") << "（YYYY，4 位，不晚于 2026）：";
        cin >> line;
        if (line.empty() && def) break;
        if (isAllDigits(line) && line.size() == 4) {
            int y = stoi(line);
            if (y > 2026) {
                cout << "（入职年份不能晚于 2026）" << endl;
                continue;
            }
            e.hire_year = y;
            break;
        }
        cout << "（入职年份必须是 4 位数字）" << endl;
    }

    // 13. 绩效奖金：必须是数字；修改模式下空输入保留原值
    while (true) {
        cout << "绩效奖金" << (def ? "[" + to_string(e.bonus) + "]" : "") << "（元）：";
        cin >> line;
        if (line.empty() && def) break;
        if (isAllDigits(line)) { e.bonus = stoi(line); break; }
        cout << "（绩效奖金必须是数字）" << endl;
    }

    // 14. 直属上级编号：输"无" 表示没有上级领导；修改模式下空输入保留原值
    cin.ignore(1000, '\n');
    while (true) {
        cout << "直属上级编号" << (def ? "[" + e.manager_id + "]" : "") << "（无上级领导请输入 无）：";
        getline(cin, line);
        if (line.empty() && def) break;
        if (line == "无") { e.manager_id = ""; break; }
        if (isAllDigits(line)) { e.manager_id = line; break; }
        cout << "（直属上级编号必须是数字，或输 无）" << endl;
    }

    return e;
}

// ============================================================
//  员工自助登录
// ============================================================
Employee* Employeelist::login(string id, string password) {
    Employee *p = find(id);
    if (!p) return nullptr;             // 编号不存在
    if (p->password != password) return nullptr;   // 密码错
    return p;
}

// 显示员工的"基本信息"（不含薪资、密码等敏感字段）
void Employeelist::displaySelf(string id) {
    Employee *p = find(id);
    if (!p) {
        cout << "[错误] 找不到编号 " << id << " 的员工。" << endl;
        return;
    }
    cout << "\n========== 我的基本信息 ==========" << endl;
    cout << "  编    号：" << p->no           << endl;
    cout << "  姓    名：" << p->name         << endl;
    cout << "  生    日：" << p->birthday.tostring() << endl;
    cout << "  学    历：" << p->education    << endl;
    cout << "  民    族：" << p->ethnicity    << endl;
    cout << "  专    业：" << p->major        << endl;
    cout << "  职    称：" << p->title        << endl;
    cout << "  部    门：" << p->department   << endl;
    cout << "  职    务：" << p->position     << endl;
    cout << "  入职年份：" << p->hire_year    << endl;
    cout << "==================================" << endl;
}

// 显示薪资信息
void Employeelist::displaySalary(string id) {
    Employee *p = find(id);
    if (!p) {
        cout << "[错误] 找不到编号 " << id << " 的员工。" << endl;
        return;
    }
    int total = p->salary + p->bonus;
    cout << "\n========== 我的薪资信息 ==========" << endl;
    cout << "  月    薪：" << p->salary  << " 元" << endl;
    cout << "  绩效奖金：" << p->bonus   << " 元" << endl;
    cout << "  --------------------------" << endl;
    cout << "  合    计：" << total      << " 元/月" << endl;
    cout << "==================================" << endl;
}

// 显示直属上级（用 manager_id 反查 EmployeeList）
void Employeelist::displayManager(string id) {
    Employee *p = find(id);
    if (!p) {
        cout << "[错误] 找不到编号 " << id << " 的员工。" << endl;
        return;
    }
    if (p->manager_id.empty()) {
        cout << "\n[信息] 您是公司最高领导，没有直属上级。" << endl;
        return;
    }
    Employee *m = find(p->manager_id);
    if (!m) {
        cout << "\n[警告] 直属上级编号 " << p->manager_id
             << " 在员工列表中不存在（可能数据不一致）。" << endl;
        return;
    }
    cout << "\n========== 我的直属上级 ==========" << endl;
    cout << "  姓    名：" << m->name       << endl;
    cout << "  编    号：" << m->no         << endl;
    cout << "  部    门：" << m->department << endl;
    cout << "  职    务：" << m->position   << endl;
    cout << "  职    称：" << m->title      << endl;
    cout << "==================================" << endl;
}

// 员工修改本人密码
bool Employeelist::changePassword(string id, string newPwd) {
    Employee *p = find(id);
    if (!p) return false;
    if (newPwd.empty()) return false;
    p->password = newPwd;
    write();        // 同步到硬盘
    return true;
}
