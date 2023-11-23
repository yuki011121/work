
#include "FILE.h"
/**
 * ���ļ�
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param sysOpenFile
 */
void openFile(string name, FileSystem fileSystem, int cur_SFD, User &user, SysOpenFile* sysOpenFile){

    int pos = checkExitsfd(name, fileSystem, cur_SFD);  //�鿴�ǵ�ǰĿ¼�µĵڼ����ļ�
    if (pos == -1){
        setFontColor(12);
        cout << "�ļ�������\n";
        return;
    }
    else{
        int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;   //�ļ���Ӧ��i�����
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
                    cout << "��ʧ�ܣ��Ѵﵽϵͳ���ļ��������\n";
                    return;
                }
                continue;
            }
            if(tmp == 0){
                tmp = i+1;  //���ļ�����λ��
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
                if(sysOpenFile[user.uOpenFile.SysOFId[i]-1].iId ==inodeNo){ //���û��Ѿ��򿪴��ļ�
                    sysOpenFile[user.uOpenFile.SysOFId[i]-1].count--;
                    setFontColor(10);
                    cout << "�Ѵ��ļ�\n";
                    return;
                }
                if(tmp2 == -1&&i == NOFILE-1)  {
                    setFontColor(12);
                    cout << "��ʧ�ܣ��Ѵﵽ�û����ļ�������������ȹرռ����ļ���������\n";
                    //��ԭϵͳ���ļ���
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
            cout << "�򿪳ɹ�\n";
        }
    }
}
/**
 * �ر��ļ�
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param sysOpenFile
 */
void closeFile(string name, FileSystem fileSystem, int cur_SFD, User &user, SysOpenFile* sysOpenFile){

    int pos = checkExitsfd(name, fileSystem, cur_SFD);  //�鿴�ǵ�ǰĿ¼�µĵڼ����ļ�
    if (pos == -1){
        setFontColor(12);
        cout << "�ļ�������\n";
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
                if(user.uOpenFile.SysOFId[i] ==tmp){ //���û��Ѿ��򿪴��ļ�
                    user.uOpenFile.SysOFId[i] = -1;
                    setFontColor(10);
                    cout << "�ѹر��ļ�\n";
                    break;
                }
            }
        }
    }
}
