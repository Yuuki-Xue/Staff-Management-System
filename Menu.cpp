#include "Menu.h"
#include "admin.h"
#include "viewer.h"
#include "employee.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

// ============================================================
//  Menu 实现
//  数据操作全部转交 elist / alist / vlist
// ============================================================
Menu::Menu(Employeelist& e, Adminlist& a)
    : elist(e), alist(a), role(0) {}

// 清屏
void Menu::clearScreen() {
    system("cls");
}

void Menu::pauseScreen() {
    cout << "\n按回车继续...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int Menu::getInt() {
    string s;
    while (true) {
        getline(cin, s);
        // 逐位检查 s 是不是纯数字
        bool ok = !s.empty();
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') { ok = false; break; }
        }
        if (ok) return stoi(s);
        cout << "[错误] 请输入整数：";
    }
}

string Menu::getLine() {
    string s;
    getline(cin, s);
    return s;
}

bool Menu::confirm(const string& msg) {
    cout << msg << " (y/n)：";
    string ans = getLine();
    return (ans == "y" || ans == "Y");
}

// ============================================================
//  登录：密码错可以重试 3 次
// ============================================================
bool Menu::handleLogin() {
    const int MAX = 3;
    int ch = 0;

    // 选择身份（0=退出，1/2/3=合法，其他=重新显示登录界面）
    while (true) {
        clearScreen();
        cout << "================================================" << endl;
        cout << "        欢迎使用公司员工管理系统               " << endl;
        cout << "================================================" << endl;
        cout << "1. 管理员登录  2. 访客登录  3. 员工登录  0. 退出系统" << endl;
        cout << "请选择身份：";
        ch = getInt();
        if (ch == 0) return false;     // 选 0 → 退出系统
        if (ch >= 1 && ch <= 3) break; // 选 1/2/3 → 进入密码验证
        cout << "[错误] 无效选项，请输入 0-3 之间的数字。" << endl;
        pauseScreen();                 // 错误时暂停，否则立刻被 clearScreen 冲掉
    }

    // 密码验证（最多 3 次）
    string account, password;
    for (int i = 0; i < MAX; i++) {
        cout << "\n[剩余 " << (MAX - i) << " 次尝试]" << endl;
        cout << "账号："; cin >> account;
        cout << "密码："; cin >> password;

        if (ch == 1 && alist.login(account, password)) {
            role = 1;
            loginName = account;
            cout << "\n[验证通过] 欢迎管理员 " << account << "！" << endl;
            pauseScreen();
            return true;
        }
        if (ch == 2 && account == "viewer" && password == "123456") {
            role = 2;
            loginName = account;
            cout << "\n[验证通过] 欢迎访客 " << account << "！" << endl;
            pauseScreen();
            return true;
        }
        if (ch == 3 && elist.login(account, password)) {
            role = 3;
            loginName = account;   // 这里存的是员工编号
            cout << "\n[验证通过] 欢迎员工 " << account << "！" << endl;
            pauseScreen();
            return true;
        }
        cout << "[错误] 账号或密码错误。" << endl;
    }
    cout << "\n[安全] 连续 " << MAX << " 次登录失败，系统退出。" << endl;
    return false;
}

// ============================================================
//  菜单打印
// ============================================================
void Menu::printAdminMenu() const {
    cout << "\n================ 主菜单（管理员） ================" << endl;
    cout << "  1. 浏览全体员工信息" << endl;
    cout << "  2. 新增员工" << endl;
    cout << "  3. 删除员工" << endl;
    cout << "  4. 修改员工信息" << endl;
    cout << "  5. 查询员工（精确 / 模糊）" << endl;
    cout << "  6. 排序显示" << endl;
    cout << "  7. 分类统计" << endl;
    cout << "  8. 账号管理" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "==================================================" << endl;
    cout << "当前用户: " << loginName << "（管理员）" << endl;
    cout << "请选择操作 (0-8): ";
}

void Menu::printViewerMenu() const {
    cout << "\n================ 主菜单（访客） ==================" << endl;
    cout << "  1. 浏览全体员工信息" << endl;
    cout << "  2. 查询员工（精确 / 模糊）" << endl;
    cout << "  3. 排序显示" << endl;
    cout << "  4. 分类统计" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "==================================================" << endl;
    cout << "当前用户: " << loginName << "（访客·只读）" << endl;
    cout << "请选择操作 (0-4): ";
}

void Menu::printEmployeeMenu() const {
    cout << "\n================ 我的工作台（员工） ==============" << endl;
    cout << "  1. 查看我的基本信息" << endl;
    cout << "  2. 查看我的薪资信息（月薪 + 绩效）" << endl;
    cout << "  3. 查看我的直属上级" << endl;
    cout << "  4. 修改我的登录密码" << endl;
    cout << "  0. 退出登录" << endl;
    cout << "==================================================" << endl;
    cout << "当前用户: " << loginName << "（员工·本人）" << endl;
    cout << "请选择操作 (0-4): ";
}

void Menu::printSearchMenu() const {
    cout << "\n----- 查询子菜单 -----" << endl;
    cout << "  1. 精确查询（整字段匹配）" << endl;
    cout << "  2. 模糊查询（子串匹配）" << endl;
    cout << "  0. 返回主菜单" << endl;
    cout << "-----------------------" << endl;
    cout << "请选择: ";
}

void Menu::printStatsMenu() const {
    cout << "\n----- 统计子菜单 -----" << endl;
    cout << "  1. 按部门统计" << endl;
    cout << "  2. 按学历统计" << endl;
    cout << "  3. 按职称统计" << endl;
    cout << "  4. 按职务统计" << endl;
    cout << "  5. 按民族统计" << endl;
    cout << "  0. 返回主菜单" << endl;
    cout << "-----------------------" << endl;
    cout << "请选择: ";
}

void Menu::printAdminAccountMenu() const {
    cout << "\n----- 管理员账号管理 -----" << endl;
    cout << "  1. 查看所有管理员账号" << endl;
    cout << "  2. 新增管理员" << endl;
    cout << "  3. 删除管理员" << endl;
    cout << "  4. 修改管理员密码" << endl;
    cout << "  0. 返回上一级" << endl;
    cout << "----------------------------" << endl;
    cout << "请选择: ";
}

// ============================================================
//  各功能入口（每个独立 handler，做完清屏 + 暂停）
//  业务逻辑全调 elist 的方法
// ============================================================
void Menu::handleBrowse() {
    clearScreen();
    cout << "--- 浏览全体员工 ---" << endl;
    elist.display();
}

void Menu::handleAdd() {
    clearScreen();
    cout << "--- 新增员工 ---" << endl;
    Employee e = elist.input(true);   // ask_id=true：让用户输入编号（内含查重）
    if (e.no.empty()) {
        // input() 内部已报错（编号重复），直接返回主菜单
        return;
    }
    elist.add(e);
    elist.write();
    cout << "[成功] 员工信息已录入并同步到硬盘。" << endl;
}

void Menu::handleDelete() {
    clearScreen();
    cout << "--- 删除员工 ---" << endl;
    cout << "请输入要删除的员工编号: ";
    string id = getLine();
    if (id.empty()) {
        cout << "[错误] 编号不能为空。" << endl;
        return;
    }
    if (!elist.find(id)) {
        cout << "[失败] 未找到编号为 " << id << " 的员工。" << endl;
        return;
    }
    if (!confirm("\n确认要删除编号 " + id + " 的员工吗？此操作不可恢复")) {
        cout << "[取消] 已放弃删除。" << endl;
        return;
    }

    // 清理下属的 manager_id 野引用（避免删除后下属查看"我的直属上级"时找不到上级）
    int cleared = 0;
    for (Employee *p = elist.ptr; p; p = p->next) {
        if (p->manager_id == id) {
            p->manager_id = "";
            cleared++;
        }
    }
    if (cleared > 0) {
        cout << "[提示] 已清理 " << cleared << " 名下属的直属上级引用。" << endl;
    }

    elist.remove(id);
    elist.write();
    cout << "[成功] 编号 " << id << " 已删除，硬盘已同步。" << endl;
}

void Menu::handleModify() {
    clearScreen();
    cout << "--- 修改员工信息 ---" << endl;
    cout << "请输入要修改的员工编号: ";
    string id = getLine();
    if (id.empty()) {
        cout << "[错误] 编号不能为空。" << endl;
        return;
    }
    Employee* orig = elist.find(id);
    if (!orig) {
        cout << "[失败] 编号不存在。" << endl;
        return;
    }
    cout << "\n请逐字段输入新值（直接回车保留原值，方括号内为当前值）：" << endl;
    Employee e = elist.input(false, orig);  // ask_id=false，def=orig：空输入保留原值
    e.no = id;
    elist.update(id, e);
    elist.write();
    cout << "[成功] 员工信息已更新，硬盘已同步。" << endl;
}

void Menu::handleSearch() {
    clearScreen();
    printSearchMenu();
    int type = getInt();
    if (type == 0) return;
    // 合法性检查：1=精确，2=模糊，其他都是无效
    if (type != 1 && type != 2) {
        cout << "[错误] 无效选项，请输入 0-2 之间的数字。" << endl;
        return;   // 返回到调用它的 menu loop，会自动 pauseScreen
    }

    cout << "请输入要查询的字段名（编号/姓名/生日/学历/民族/专业/职称/部门/职务）: ";
    string field = getLine();
    cout << "请输入要查询的值: ";
    string value = getLine();

    if (field.empty() || value.empty()) {
        cout << "[错误] 字段名和值均不能为空。" << endl;
        return;
    }
    elist.search(field, value, type == 1);
}

void Menu::handleSort() {
    clearScreen();
    cout << "--- 排序显示 ---" << endl;
    cout << "支持的排序字段：编号 / 姓名 / 生日 / 学历 / 民族 / 专业 / 职称 / 部门 / 职务" << endl;
    cout << "请输入要排序的字段名: ";
    string field = getLine();
    if (field.empty()) {
        cout << "[错误] 字段名不能为空。" << endl;
        return;
    }
    elist.sort(field);
    elist.write();
    cout << "[成功] 已按 [" << field << "] 升序排序并保存。" << endl;
    elist.display();
}

void Menu::handleStatistics() {
    clearScreen();
    printStatsMenu();
    int type = getInt();
    if (type == 0) return;
    string field;
    string title = "统计结果";
    switch (type) {
        case 1: field = "department"; title = "按部门统计"; break;
        case 2: field = "education";  title = "按学历统计"; break;
        case 3: field = "title";      title = "按职称统计"; break;
        case 4: field = "position";   title = "按职务统计"; break;
        case 5: field = "ethnicity";  title = "按民族统计"; break;
        default: cout << "[错误] 无效选项。" << endl; return;
    }
    cout << "\n===== " << title << " =====" << endl;
    elist.stats(field);
}

// ============================================================
//  主菜单循环（按角色选 adminMenuLoop / viewerMenuLoop）
// ============================================================
void Menu::adminMenuLoop() {
    int choice = -1;
    while (true) {
        clearScreen();
        printAdminMenu();
        choice = getInt();
        if (choice == 0) break;
        switch (choice) {
            case 1: handleBrowse();      break;
            case 2: handleAdd();         break;
            case 3: handleDelete();      break;
            case 4: handleModify();      break;
            case 5: handleSearch();      break;
            case 6: handleSort();        break;
            case 7: handleStatistics();  break;
            case 8: accountMenuLoop();   break;   // 进入账号管理子菜单
            default: cout << "[错误] 无效指令，请输入 0-8 之间的数字。" << endl;
                     pauseScreen();        // 错误时也暂停，否则错误信息被下次 clearScreen 冲掉
        }
        if (choice >= 1 && choice <= 8) pauseScreen();
    }
}

// ============================================================
//  账号管理子循环（只有管理员能进）
// ============================================================
//  账号管理总入口（选择管管理员 or 访客）
// ============================================================
void Menu::accountMenuLoop() {
    int choice = -1;
    while (true) {
        clearScreen();
        cout << "\n----- 账号管理 -----" << endl;
        cout << "  1. 查看所有管理员账号 / 新增 / 删除 / 改密码" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "-------------------" << endl;
        cout << "请选择: ";
        choice = getInt();
        if (choice == 0) break;
        if (choice == 1) {
            adminAccountMenuLoop();          // 进入管理员账号子菜单
            pauseScreen();                    // 从子菜单回来后暂停，让用户看清已返回
        }
        else {
            cout << "[错误] 无效指令，请输入 0-1 之间的数字。" << endl;
            pauseScreen();                    // 错误时也暂停
        }
    }
}

// ============================================================
//  管理员账号子循环（增删改查管理员账号）
// ============================================================
void Menu::adminAccountMenuLoop() {
    int choice = -1;
    while (true) {
        clearScreen();
        printAdminAccountMenu();
        choice = getInt();
        if (choice == 0) break;
        switch (choice) {
            case 1: handleAccountList();       break;
            case 2: handleAccountAdd();        break;
            case 3: handleAccountDelete();     break;
            case 4: handleAccountChangePwd();  break;
            default: cout << "[错误] 无效指令，请输入 0-4 之间的数字。" << endl;
                     pauseScreen();
        }
        if (choice >= 1 && choice <= 4) pauseScreen();
    }
}

// ============================================================
//  账号管理 4 个 handler
// ============================================================
void Menu::handleAccountList() {
    clearScreen();
    cout << "--- 当前所有管理员账号 ---" << endl;
    alist.displayAll();
}

void Menu::handleAccountAdd() {
    clearScreen();
    cout << "--- 新增管理员 ---" << endl;
    string no, name, pass;
    cout << "账号（必填，唯一）："; cin >> no;
    if (no.empty()) {
        cout << "[错误] 账号不能为空。" << endl;
        return;
    }
    if (alist.find(no)) {
        cout << "[失败] 账号 " << no << " 已存在。" << endl;
        return;
    }
    cout << "姓名："; cin >> name;
    if (name.empty()) name = no;
    cout << "密码（默认 123456）："; cin >> pass;
    if (pass.empty()) pass = "123456";

    Admin a(no, name, pass);
    alist.add(a);
    alist.write();
    cout << "[成功] 已新增管理员 " << no << "（" << name << "）。" << endl;
}

void Menu::handleAccountDelete() {
    clearScreen();
    cout << "--- 删除管理员 ---" << endl;
    // 安全保护：至少保留一个管理员
    if (alist.size <= 1) {
        cout << "[失败] 系统至少需要保留 1 个管理员账号，无法删除最后一个。" << endl;
        return;
    }
    string no;
    cout << "请输入要删除的管理员账号："; cin >> no;
    if (no == loginName) {
        cout << "[失败] 不能删除自己（当前登录的管理员）。" << endl;
        return;
    }
    if (!alist.find(no)) {
        cout << "[失败] 账号 " << no << " 不存在。" << endl;
        return;
    }
    if (!confirm("\n确认要删除账号 " + no + " 吗？")) {
        cout << "[取消] 已放弃删除。" << endl;
        return;
    }
    alist.remove(no);
    alist.write();
    cout << "[成功] 管理员 " << no << " 已删除，硬盘已同步。" << endl;
}

void Menu::handleAccountChangePwd() {
    clearScreen();
    cout << "--- 修改管理员密码 ---" << endl;
    string no, npwd;
    cout << "请输入要修改密码的管理员账号："; cin >> no;
    if (!alist.find(no)) {
        cout << "[失败] 账号 " << no << " 不存在。" << endl;
        return;
    }
    cout << "新密码（不能为空）："; cin >> npwd;
    if (npwd.empty()) {
        cout << "[错误] 新密码不能为空。" << endl;
        return;
    }
    if (alist.changePassword(no, npwd)) {
        cout << "[成功] 账号 " << no << " 的密码已修改并同步到硬盘。" << endl;
    } else {
        cout << "[失败] 修改密码失败。" << endl;
    }
}

// ============================================================
//  访客账号硬编码为 viewer/123456，handleLogin 里直接比较
// ============================================================

void Menu::viewerMenuLoop() {
    int choice = -1;
    while (true) {
        clearScreen();
        printViewerMenu();
        choice = getInt();
        if (choice == 0) break;
        switch (choice) {
            case 1: handleBrowse();         break;
            case 2: handleSearch();         break;
            case 3: handleSort();           break;
            case 4: handleStatistics();     break;
            default: cout << "[错误] 无效指令，请输入 0-4 之间的数字。" << endl;
                     pauseScreen();
        }
        if (choice >= 1 && choice <= 4) pauseScreen();
    }
}

// ============================================================
//  员工自助菜单循环（看自己信息 / 改密码）
// ============================================================
void Menu::employeeMenuLoop() {
    int choice = -1;
    while (true) {
        clearScreen();
        printEmployeeMenu();
        choice = getInt();
        if (choice == 0) break;
        switch (choice) {
            case 1: handleSelfBasic();       break;
            case 2: handleSelfSalary();      break;
            case 3: handleSelfManager();     break;
            case 4: handleSelfChangePwd();   break;
            default: cout << "[错误] 无效指令，请输入 0-4 之间的数字。" << endl;
                     pauseScreen();
        }
        if (choice >= 1 && choice <= 4) pauseScreen();
    }
}

// ============================================================
//  员工自助各功能 handler
// ============================================================
void Menu::handleSelfBasic() {
    clearScreen();
    elist.displaySelf(loginName);
}

void Menu::handleSelfSalary() {
    clearScreen();
    elist.displaySalary(loginName);
}

void Menu::handleSelfManager() {
    clearScreen();
    elist.displayManager(loginName);
}

void Menu::handleSelfChangePwd() {
    clearScreen();
    cout << "--- 修改我的登录密码 ---" << endl;
    cout << "当前账号：" << loginName << endl;
    cout << "原密码："; string oldp; cin >> oldp;
    Employee *p = elist.find(loginName);
    if (!p || p->password != oldp) {
        cout << "[错误] 原密码不正确，未做修改。" << endl;
        return;
    }
    cout << "新密码（不能为空）："; string newp; cin >> newp;
    if (newp.empty()) {
        cout << "[错误] 新密码不能为空。" << endl;
        return;
    }
    if (newp == oldp) {
        cout << "[提示] 新密码与原密码相同，未做修改。" << endl;
        return;
    }
    if (elist.changePassword(loginName, newp)) {
        cout << "[成功] 密码已修改，硬盘已同步。" << endl;
    } else {
        cout << "[失败] 修改密码出错。" << endl;
    }
}

// ============================================================
//  主入口：登录成功后按角色进入对应菜单循环
//  起止提示：开始时告知已读取员工数，结束时告知已保存 + 祝福语
// ============================================================
void Menu::run() {
    if (!handleLogin()) return;

    // === 开始提示：告知已从 employees.txt 读取多少条 ===
    cout << "\n[系统] 已从 employees.txt 中读取 " << elist.size
         << " 条员工记录。" << endl;
    pauseScreen();

    // === 进入对应角色菜单循环 ===
    if (role == 1)            adminMenuLoop();
    else if (role == 2)       viewerMenuLoop();
    else if (role == 3)       employeeMenuLoop();

    // === 结束提示：数据已同步 + 祝福语 ===
    cout << "\n================================================" << endl;
    cout << "[系统] 所有修改已同步到 employees.txt（共 "
         << elist.size << " 条记录）。" << endl;
    cout << "================================================" << endl;
    cout << "\n  愿你眼里有光，心中有暖，\n"
         << "  祝你有一个美好的一天！再见～\n" << endl;
}
