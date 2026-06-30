# 公司员工管理系统（C++ 课程设计）

> C++ 程序设计课程设计 — 2026 春季任务书第 3 题
> 控制台版员工信息管理系统，支持管理员、员工、访客三类角色登录与文件持久化

## 功能概览

- **三类角色登录**：管理员 / 员工 / 访客（默认密码 `123456`）
- **管理员**：增删改查员工、增删管理员、改密、按部门 / 学历 / 工资段统计
- **员工**：查看本人信息、修改本人密码
- **访客**：浏览员工列表（脱敏，不显示薪资 / 密码 / 上级）
- **文件持久化**：所有数据存于 `*.txt`，启动自动加载，修改实时回写

## 默认账号

| 角色 | 账号 | 密码 |
|---|---|---|
| 管理员 | `admin` | `123` |
| 访客 | `viewer` | `123456` |
| 员工 | 任意 `1001`–`1010` | `123456` |

> 实际账号与员工列表见 `admins.txt` / `viewers.txt` / `employees.txt`。

## 工程结构

```
SMH/
├── people.{h,cpp}        基类：人员共性（姓名 / 编号）
├── employee.{h,cpp}      员工类（继承 people）
├── admin.{h,cpp}         管理员类（继承 people）
├── viewer.{h,cpp}        访客类（继承 people）
├── employeelist.{h,cpp}  员工链表 + 增删改查 + 登录验证
├── adminlist.{h,cpp}     管理员链表 + 登录验证 + 改密
├── date.{h,cpp}          日期工具（解析 / 格式化）
├── Menu.{h,cpp}          主菜单与各角色子菜单
├── main.cpp              程序入口
├── SMH.slnx              Visual Studio 解决方案（新格式）
├── SMH.vcxproj           VS 项目文件
├── *.txt                 数据文件
├── .gitignore
└── README.md
```

## 编译与运行

### 方式一：Visual Studio 2022

1. 双击 `SMH.slnx`，VS 2022 自动打开
2. 顶部配置选 `Debug | x64`（或 `Release | x64`）
3. 按 `F5` 运行

> 需要安装 VS 工作负载"**使用 C++ 的桌面开发**"。

### 方式二：命令行（MinGW / clang / g++）

```bash
cd SMH
g++ -std=c++17 -O2 -o SMH.exe \
    main.cpp people.cpp employee.cpp employeelist.cpp \
    admin.cpp adminlist.cpp viewer.cpp date.cpp Menu.cpp
SMH.exe
```

> 头文件通过源文件里的 `#include` 自动处理，无需列出。

## 数据文件格式

| 文件 | 分隔 | 字段 |
|---|---|---|
| `admins.txt` | 制表符 | 账号 / 姓名 / 密码 |
| `viewers.txt` | 制表符 | 账号 / 姓名 / 密码 |
| `employees.txt` | 逗号 | 编号,姓名,生日,学历,专业,职位,部门,上级,密码,月薪,入职年份,绩效,上级编号 |

> 数据文件使用 **UTF-8** 编码（含中文姓名 / 部门），源文件统一 **UTF-8 + BOM**，请用支持 UTF-8 的编辑器打开。

## 已知限制

- 控制台编码建议设为 UTF-8；中文在 GBK 控制台可能显示乱码
- 文件并发安全未做（仅适合单机单进程）
- 员工编号不自动回收（删除后留空位，新员工使用新编号）
