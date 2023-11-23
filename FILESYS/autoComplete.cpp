#include "FILE.h"

static string com[com_num] = { "link", "cd", "create", "rname",
                        "mkdir", "find","write", "read",
                        "deld", "delf","copy", "cut",
                        "paste", "cd..", "cd/", "ls",
                        "clear", "format", "logout", "exit",
                        "help", "print", "open" ,"close" };
/**
 *
 * @param name
 * @param fileSystem
 * @param cur_SFD
 */
void cin_name(string& name, FileSystem fileSystem, int cur_SFD, int& flag) {
    char c;
c1:     while ((c = getch()) == ' ' && name.size() == 0)putchar(' ');     //除去前面输入的空格
    while (c == 13) goto c1;    //如果一直输入的是回车键则会在21.22之间循环执行直到输入的不是回车键
    while (c > 32) {    //将键盘输入的非控制字符存入name
        name += c;
        cout << c;
        c = getch();
    }
    if (c == '\t') {    //键盘输入的是tab则进行文件或目录名补全
        int pos, num = 0;
        for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i) {
            if (fileSystem.sfd[cur_SFD].sfdVec[i].name.find(name) != string::npos) {//遍历文件系统目录块中每个目录项的文件名查找是否有匹配的name子串
                pos = i;
                num++;
            }
        }
        if (num == 1) {     //如果符合当前输入的指令只有一个则赋给name，输入结束
            for (int i = 0; i < name.size(); ++i)putchar('\b');    //将光标从当前位置向左移动一个字符，清空原本输入的name以便将找到的匹配的指令赋给name
            cout << fileSystem.sfd[cur_SFD].sfdVec[pos].name;
            name = fileSystem.sfd[cur_SFD].sfdVec[pos].name;
            return;
        }
        else cin_name(name, fileSystem, cur_SFD, flag);    //如果没有找到匹配的文件名或目录名或者找到多个不能确定的匹配名则继续输入
    }
    else if (c == 8) {     //键盘输入的是退格则删除上一个字符
        if (name.size() > 0) {
            name.erase(name.size() - 1);    //如果有输入则删除最后一个字符
            fflush(stdout); putchar('\b'); fflush(stdout);     //将输出缓冲区中的内容输出到屏幕上并清空输出缓冲区
            putchar(' ');
            fflush(stdout);	putchar('\b'); fflush(stdout);
        }
        cin_name(name, fileSystem, cur_SFD, flag);    //继续输入
    }
    else {
        if (c == 13) {    //键盘输入的回车键则结束输入
            cout << endl;
            flag = 0;
        }
        else cout << c;
        return;
    }
}

/**
 * 指令输入
 * @param in
 */
void cin_command(string& in, int& flag) {
    char c;
    while ((c = getch()) == ' ' && in.size() == 0)putchar(' ');    //除去前面输入的空格

    while (c > 32) {
        in += c;    //将键盘输入的非控制字符存入in
        cout << c;
        c = getch();
    }
    if (c == '\t') {   //键盘输入的是tab则进行指令补全
        int pos, num = 0;
        for (int i = 0; i < com_num; ++i) {
            if (com[i].find(in) != string::npos) {   //查找字符串com[i]中是否包含子串in，找不到则返回string::npos，此情况是找到符合当前输入的指令
                num++;
                pos = i;
            }
        }
        if (num == 1) {    //如果符合当前输入的指令只有一个则赋给in，输入结束
            for (int i = 0; i < in.size(); ++i)putchar('\b');    //清空原本输入的in以便将找到的匹配的指令赋给in
            cout << com[pos];
            in = com[pos];
            return;
        }
        else cin_command(in, flag);    //如果没有找到合适的指令则继续输入
    }
    else if (c == 8) {      //键盘输入的是退格则删除上一个字符
        if (in.size() > 0) {
            in.erase(in.size() - 1);    //删除最后一个字符
            fflush(stdout); putchar('\b'); fflush(stdout);    //将输出缓冲区中的内容输出到屏幕上并清空输出缓冲区
            putchar(' ');
            fflush(stdout);	putchar('\b'); fflush(stdout);
        }
        cin_command(in, flag);    //继续输入
    }
    else {
        if (c == 13) {       //键盘输入的回车键则结束输入
            cout << endl;
            flag = 0;
        }
        else cout << c;
        return;
    }
}