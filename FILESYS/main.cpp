#include "FILE.h"
int main()
{
    User curUser;//ȫ�ֱ�������־��ǰ���ڷ����ļ�ϵͳ���û�
    curUser.userName = "";
    int iNode[INODE_NUM] = { 0 };         //i���λ��ͼ��0��ʾռ�ݣ�1��ʾ����
    int diskBlock[DISK_NUM] = { 0 };     //���̿�λ��ͼ��0��ʾռ�ݣ�1��ʾ����
    int SFDBlock[SFD_NUM] = { 0 };      //Ŀ¼λ��ͼ��0��ʾռ�ݣ�1��ʾ����
    SysOpenFile sysOFile[SYSOPENFILE] = {{-1,"",0,-1},};
    int cur_SFD=0;        //��ǰ����sfd����ǰ����Ŀ¼
    int copy_flag = 0;	//ճ�����־
    SingleSFD copySFD = {"", 0, 1}; //ճ����
    stack<int> staSFD;   //��¼Ŀ¼ջ
    FileSystem fileSystem;  //�ļ�ϵͳ
    initOpenFileList(sysOFile);
    initFileSystem(iNode, diskBlock, SFDBlock, &fileSystem, &staSFD);
    login(curUser);
    display(curUser, &cur_SFD, &staSFD, sysOFile,&fileSystem,
            &copy_flag, iNode, diskBlock, SFDBlock, &copySFD);
    return 0;
}




