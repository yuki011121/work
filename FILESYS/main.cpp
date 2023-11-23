#include "FILE.h"
int main()
{
    User curUser;//全局变量，标志当前正在访问文件系统的用户
    curUser.userName = "";
    int iNode[INODE_NUM] = { 0 };         //i结点位势图，0表示占据，1表示空闲
    int diskBlock[DISK_NUM] = { 0 };     //磁盘块位势图，0表示占据，1表示空闲
    int SFDBlock[SFD_NUM] = { 0 };      //目录位势图，0表示占据，1表示空闲
    SysOpenFile sysOFile[SYSOPENFILE] = {{-1,"",0,-1},};
    int cur_SFD=0;        //当前所在sfd，当前所在目录
    int copy_flag = 0;	//粘贴板标志
    SingleSFD copySFD = {"", 0, 1}; //粘贴板
    stack<int> staSFD;   //记录目录栈
    FileSystem fileSystem;  //文件系统
    initOpenFileList(sysOFile);
    initFileSystem(iNode, diskBlock, SFDBlock, &fileSystem, &staSFD);
    login(curUser);
    display(curUser, &cur_SFD, &staSFD, sysOFile,&fileSystem,
            &copy_flag, iNode, diskBlock, SFDBlock, &copySFD);
    return 0;
}




