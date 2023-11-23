
#include "FILE.h"

/**
 * 推出前保存SFD内容
 * @param SFDBlock
 * @param fileSystem
 */
void exitSFD(int* SFDBlock, FileSystem fileSystem){

    freopen("sfdContext.txt", "w", stdout);

    for (int i = 1; i < 512; i++){
        if (!SFDBlock[i]){
            printf("  %d  ", fileSystem.sfd[i].sfdNum);      //sdf 数量
            //cout<<"  "<<fileSystem.sfd[i].sfdNum<<"  ";
            for (int j = 0; j < fileSystem.sfd[i].sfdNum; j++){
                cout << "  " << fileSystem.sfd[i].sfdVec[j].name << "  ";   //每一个目录的名字
                printf("  %d  %d", fileSystem.sfd[i].sfdVec[j].id, fileSystem.sfd[i].sfdVec[j].delink);     //所对应的i结点编号
                //cout<<fileSystem.sfd[i].sfdVec[j].name<<"  "<<fileSystem.sfd[i].sfdVec[j].id<<"  ";
            }
        }
    }

    fclose(stdout);
    freopen("CON", "w", stdout);
}

/**
 * 退出前保存磁盘块内容
 * @param diskBlock
 * @param fileSystem
 * @return
 */
void exitDiskBlock(int* diskBlock, FileSystem fileSystem){

    //写回磁盘块内容
    freopen("diskBlock.txt", "w", stdout);
    for (int i = 0; i < 512; i++){
        if (!diskBlock[i]){
            printf("  %d ", fileSystem.diskBlock[i].strNum);  //文件占用磁盘块个数
            /*cout<<fileSystem.diskBlock[i].strNum;
            string str;
            for (int j = 0; j < fileSystem.diskBlock[i].file.size(); j++){
                if (fileSystem.diskBlock[i].file[j] == ' ' && str.size() == 0)
                    continue;
                else if (fileSystem.diskBlock[i].file[j] == ' '){
                    cout << " " << str << " ";  //文件内容
                    str.clear();
                }
                else{
                    str += fileSystem.diskBlock[i].file[j];
                }
            }
            cout << " " << str << " ";*/
            cout << fileSystem.diskBlock[i].file;
        }
    }

    fclose(stdout);
    freopen("CON", "w", stdout);
}

/**
 * 退出前保存i节点内容
 * @param iNode
 * @param fileSystem
 */
void exitINode(int* iNode, FileSystem fileSystem){

    //写回i结点内容
    freopen("iNodeContext.txt", "w", stdout);
    for (int i = 9; i < 128; i++){
        if (!iNode[i]){
            //
            printf("  %d  %d  %d  %d  %d  ", fileSystem.iNode[i].id, fileSystem.iNode[i].type,
                   fileSystem.iNode[i].sfd_id, fileSystem.iNode[i].filelen, fileSystem.iNode[i].qcount);
            //cout<<"  "<<fileSystem.iNode[i].id<<"  "<<fileSystem.iNode[i].type<<"  "<<fileSystem.iNode[i].sfd_id<<"  "<<fileSystem.iNode[i].filelen<<"  "<<fileSystem.iNode[i].qcount<<"  ";
            for (int j = 0; j < 8; j++)
                printf("  %d  ", fileSystem.iNode[i].auth[j]);
            //cout<<"  "<<fileSystem.iNode[i].auth[j]<<"  ";
            if (fileSystem.iNode[i].type == 0){
                printf("  %d  %d  ", fileSystem.iNode[i].diskBlockNum, fileSystem.iNode[i].diskBlockId);
                //cout<<"  "<<fileSystem.iNode[i].diskBlockNum<<"  ";
                //cout<<"  "<<fileSystem.iNode[i].diskBlockId<<"  ";
            }
        }
    }

    fclose(stdout);
    freopen("CON", "w", stdout);
}


/**
 * 退出前保存超级块内容
 * @param fileSystem
 * @param diskBlock
 */
void exitSuperBlock(FileSystem fileSystem, int* diskBlock){

    //写回超级块内容
    freopen("superBlock.txt", "w", stdout);
    printf("  %d  %d  ", fileSystem.superBlock.i_node, fileSystem.superBlock.freei_node);
    //cout<<"  "<<fileSystem.superBlock.i_node<<"  "<<fileSystem.superBlock.freei_node;
    for (int i = 0; i < fileSystem.superBlock.freei_node; i++){
        printf("  %d  ", fileSystem.superBlock.freeiid[i]);
        //cout<<"  "<<fileSystem.superBlock.freeiid[i]<<"  ";
    }

    printf("  %d  %d  ", fileSystem.superBlock.sfd, fileSystem.superBlock.free_SFD);
    //cout<<"  "<<fileSystem.superBlock.sfd<<"  "<<fileSystem.superBlock.free_SFD<<"  ";
    for (int i = 0; i < fileSystem.superBlock.free_SFD; i++){
        printf("  %d  ", fileSystem.superBlock.freeSFD[i]);
        //cout<<"  "<<fileSystem.superBlock.freeSFD[i]<<"  ";
    }
    printf("  %d  %d  ", fileSystem.superBlock.disk, fileSystem.superBlock.freeDisk);
    //cout<<"  "<<fileSystem.superBlock.disk<<"  "<<fileSystem.superBlock.freeDisk<<"  ";

    fclose(stdout);
    freopen("CON", "w", stdout);

    freopen("freeBlock.txt", "w", stdout);
    for (int i = 0; i < 512; i++){
        if (diskBlock[i] == 1){
            printf("  %d  ", i);
            //cout<<" "<<i<<" ";
        }
    }

    fclose(stdout);
    freopen("CON", "w", stdout);
}

/**
 * 退出系统
 * @param fileSystem
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 */
void exitSystem(FileSystem fileSystem, int* iNode, int* SFDBlock, int* diskBlock){
    MessageBox(NULL, TEXT("欢迎您再次使用！"), TEXT("HELLO"), MB_OK);
    exitSFD(SFDBlock, fileSystem);
    exitDiskBlock(diskBlock, fileSystem);
    exitINode(iNode, fileSystem);
    exitSuperBlock(fileSystem, diskBlock);
}