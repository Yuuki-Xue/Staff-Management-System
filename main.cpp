#include <iostream>
#include "adminlist.h"
#include "employeelist.h"
#include "Menu.h"
using namespace std;

int main() {
    // 加载账号
    Adminlist alist;
    alist.loadfile();

    // 默认账号（首次运行写盘）
    if (alist.ptr == nullptr) {
        Admin a("admin", "管理员", "123456");
        alist.add(a);
        alist.write();
    }
    // 访客账号硬编码为 viewer/123456，不需要文件存储

    // 加载员工数据
    Employeelist elist;
    elist.loadfile();

    // 交给 Menu 控制
    Menu menu(elist, alist);
    menu.run();

    return 0;
}
