#ifndef MENU_H
#define MENU_H

#include <string>
#include "employeelist.h"
#include "adminlist.h"
using namespace std;

// ============================================================
//  Menu —— 视图/控制层
//  数据操作全转交 elist / alist
//  注：viewer 改为硬编码单账号（viewer/123456），不再用链表
// ============================================================
class Menu {
public:
    Menu(Employeelist& e, Adminlist& a);
    void run();

private:
    Employeelist& elist;
    Adminlist& alist;
    int role;           // 0=未登录  1=admin  2=viewer  3=员工
    string loginName;   // 当前登录账号（员工登录时存员工编号）
    // 屏幕工具
    void clearScreen();
    void pauseScreen();

    // 输入工具
    int getInt();
    string getLine();
    bool confirm(const string& msg);

    // 登录
    bool handleLogin();

    // 主菜单循环（按角色选 adminMenuLoop / viewerMenuLoop / employeeMenuLoop）
    void adminMenuLoop();
    void viewerMenuLoop();
    void employeeMenuLoop();
    void accountMenuLoop();           // 管理员专属：账号管理子循环
    void adminAccountMenuLoop();      // 管理员账号子菜单循环

    // 菜单打印
    void printAdminMenu() const;
    void printViewerMenu() const;
    void printEmployeeMenu() const;
    void printSearchMenu() const;
    void printStatsMenu() const;
    void printAdminAccountMenu() const;   // 管理员账号子菜单

    // 各功能入口（管理员 / 访客共享）
    void handleBrowse();
    void handleAdd();
    void handleDelete();
    void handleModify();
    void handleSearch();
    void handleSort();
    void handleStatistics();

    // 员工自助功能入口
    void handleSelfBasic();
    void handleSelfSalary();
    void handleSelfManager();
    void handleSelfChangePwd();

    // 管理员账号管理（子菜单的 4 个 handler）
    void handleAccountList();
    void handleAccountAdd();
    void handleAccountDelete();
    void handleAccountChangePwd();
};

#endif
