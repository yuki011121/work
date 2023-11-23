
#include "FILE.h"


//������һ��Ŀ¼
int goNextDir(string filename, FileSystem fileSystem, int* cur_SFD){
    int pos = -1;
    for (int i = 0; i < fileSystem.sfd[*cur_SFD].sfdVec.size(); i++){
        if (fileSystem.sfd[*cur_SFD].sfdVec[i].name == filename){
            pos = i;
            break;
        }
    }
    if (pos == -1){
        setFontColor(12);
        cout << "�����ڵ�Ŀ¼������ʧ�ܣ�\n";
        return 0;
    }

    int cur_iNode = fileSystem.sfd[*cur_SFD].sfdVec[pos].id;
    if (fileSystem.iNode[cur_iNode].type == 0){
        setFontColor(12);
        cout << "�����Ϊ�ļ���������ʧ�ܣ�\n";
        return 0;
    }
    *cur_SFD = fileSystem.iNode[cur_iNode].sfd_id;
    return 1;
}


//��õ�ǰĿ¼��i����
int getInodeNum(int* iNode, FileSystem fileSystem, int cur_SFD){
    int pos = -1;
    for (int i = 0; i < 128; i++){
        if (iNode[i] == 0 && fileSystem.iNode[i].sfd_id == cur_SFD){
            pos = i;
            break;
        }
    }
    return pos;
}

//��ʾ��ǰĿ¼�µ������ļ���Ŀ¼
void showSFD(FileSystem fileSystem, int cur_SFD){
    for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
        cout << fileSystem.sfd[cur_SFD].sfdVec[i].name << "\t\t";
        int id = fileSystem.sfd[cur_SFD].sfdVec[i].id;
        if (fileSystem.iNode[id].type == 0){
            cout << "file" << endl;
        }
        else
        {
            cout << "dir" << endl;
        }
    }
    cout << endl;
}

//�ӵ�ǰĿ¼��ʼ�����ļ�
void find_filedir(string cur_path, string name, FileSystem fileSystem, int cur_SFD)
{
    for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i){
        if (fileSystem.sfd[cur_SFD].sfdVec[i].name == name){
            cout << name << "\t\t" << cur_path << "\\" << name << endl;
            break;
        }
    }
    for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i){
        if (fileSystem.sfd[cur_SFD].sfdVec[i].id != -1){
            int temp_SFD = cur_SFD;
            cur_SFD = fileSystem.iNode[fileSystem.sfd[cur_SFD].sfdVec[i].id].sfd_id;
            find_filedir(cur_path + "\\" + fileSystem.sfd[temp_SFD].sfdVec[i].name, name, fileSystem, cur_SFD);
            cur_SFD = temp_SFD;
        }
    }
}
