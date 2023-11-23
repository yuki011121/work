
#include "FILE.h"
/**
 * 打开文件
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param sysOpenFile
 */
void openFile(string name, FileSystem fileSystem, int cur_SFD, User &user, SysOpenFile* sysOpenFile){

    int pos = checkExitsfd(name, fileSystem, cur_SFD);  //查看是当前目录下的第几个文件
    if (pos == -1){
        setFontColor(12);
        cout << "文件不存在\n";
        return;
    }
    else{
        int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;   //文件对应的i结点编号
        int tmp = 0;
        int flag = 0;
        for(int i = 0;i < SYSOPENFILE;i++){
            if(sysOpenFile[i].id != -1){
                if(sysOpenFile[i].iId == inodeNo){
                    sysOpenFile[i].count++;
                    tmp = i+1;
                    flag = 1;
                    break;
                }
                if(tmp == 0&&i == SYSOPENFILE-1) {
                    setFontColor(12);
                    cout << "打开失败，已达到系统打开文件最大项数\n";
                    return;
                }
                continue;
            }
            if(tmp == 0){
                tmp = i+1;  //打开文件表有位置
            }
        }
        if(flag == 0){
            sysOpenFile[tmp-1].id = tmp;
            sysOpenFile[tmp-1].iId = inodeNo;
            sysOpenFile[tmp-1].count = 1;
            sysOpenFile[tmp-1].fileName = name;
        }
        int tmp2 = -1;
        for(int i = 0;i < NOFILE;i++){
            if(user.uOpenFile.SysOFId[i]!=-1){
                if(sysOpenFile[user.uOpenFile.SysOFId[i]-1].iId ==inodeNo){ //该用户已经打开此文件
                    sysOpenFile[user.uOpenFile.SysOFId[i]-1].count--;
                    setFontColor(10);
                    cout << "已打开文件\n";
                    return;
                }
                if(tmp2 == -1&&i == NOFILE-1)  {
                    setFontColor(12);
                    cout << "打开失败，已达到用户打开文件最大项数，请先关闭几个文件后再重试\n";
                    //还原系统打开文件表
                    sysOpenFile[tmp-1].id = -1;
                    sysOpenFile[tmp-1].iId = -1;
                    sysOpenFile[tmp-1].count = 0;
                    return;
                }
            }
            if(tmp2 == -1){
                tmp2 = i;
            }

        }
        if(tmp2!=-1){
            user.uOpenFile.SysOFId[tmp2] = tmp;
            setFontColor(10);
            cout << "打开成功\n";
        }
    }
}
/**
 * 关闭文件
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param sysOpenFile
 */
void closeFile(string name, FileSystem fileSystem, int cur_SFD, User &user, SysOpenFile* sysOpenFile){

    int pos = checkExitsfd(name, fileSystem, cur_SFD);  //查看是当前目录下的第几个文件
    if (pos == -1){
        setFontColor(12);
        cout << "文件不存在\n";
        return;
    }
    else{
        int tmp = 0;
        for(int i = 0;i < SYSOPENFILE;i++){
            if(sysOpenFile[i].id != -1){
                if(sysOpenFile[i].fileName == name){
                    sysOpenFile[i].id = -1;
                    sysOpenFile[i].count = 0;
                    sysOpenFile[i].iId = -1;
                    setFontColor(10);
                    tmp = i+1;
                    break;
                }
                continue;
            }
        }
        if(tmp != 0)
        for(int i = 0;i < NOFILE;i++){
            if(user.uOpenFile.SysOFId[i]!=-1){
                if(user.uOpenFile.SysOFId[i] ==tmp){ //该用户已经打开此文件
                    user.uOpenFile.SysOFId[i] = -1;
                    setFontColor(10);
                    cout << "已关闭文件\n";
                    break;
                }
            }
        }
    }
}
