
#include "FILE.h"
/**
 * 格式化文件系统
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 * @param user
 */
void formatUser(FileSystem* fileSystem, int cur_SFD, int* iNode, int* SFDBlock, int* diskBlock, string user){
    //登录时可选格式化所登录用户文件夹下的所有文件
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size();){
        //cout<< fileSystem.sfd[cur_SFD].sfdVec.size();
        int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[i].id;
        int type = (*fileSystem).iNode[inodeNo].type;
        if (type == 1) deleteDir((*fileSystem).sfd[cur_SFD].sfdVec[i].name, fileSystem, cur_SFD, iNode, SFDBlock, diskBlock, user);
        else freeFile((*fileSystem).sfd[cur_SFD].sfdVec[i].name, fileSystem, cur_SFD, user, iNode, diskBlock, SFDBlock);
    }
}