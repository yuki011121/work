
#include "FILE.h"
/**
 * ��ʽ���ļ�ϵͳ
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 * @param user
 */
void formatUser(FileSystem* fileSystem, int cur_SFD, int* iNode, int* SFDBlock, int* diskBlock, string user){
    //��¼ʱ��ѡ��ʽ������¼�û��ļ����µ������ļ�
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size();){
        //cout<< fileSystem.sfd[cur_SFD].sfdVec.size();
        int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[i].id;
        int type = (*fileSystem).iNode[inodeNo].type;
        if (type == 1) deleteDir((*fileSystem).sfd[cur_SFD].sfdVec[i].name, fileSystem, cur_SFD, iNode, SFDBlock, diskBlock, user);
        else freeFile((*fileSystem).sfd[cur_SFD].sfdVec[i].name, fileSystem, cur_SFD, user, iNode, diskBlock, SFDBlock);
    }
}