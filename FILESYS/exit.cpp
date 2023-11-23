
#include "FILE.h"

/**
 * �Ƴ�ǰ����SFD����
 * @param SFDBlock
 * @param fileSystem
 */
void exitSFD(int* SFDBlock, FileSystem fileSystem){

    freopen("sfdContext.txt", "w", stdout);

    for (int i = 1; i < 512; i++){
        if (!SFDBlock[i]){
            printf("  %d  ", fileSystem.sfd[i].sfdNum);      //sdf ����
            //cout<<"  "<<fileSystem.sfd[i].sfdNum<<"  ";
            for (int j = 0; j < fileSystem.sfd[i].sfdNum; j++){
                cout << "  " << fileSystem.sfd[i].sfdVec[j].name << "  ";   //ÿһ��Ŀ¼������
                printf("  %d  %d", fileSystem.sfd[i].sfdVec[j].id, fileSystem.sfd[i].sfdVec[j].delink);     //����Ӧ��i�����
                //cout<<fileSystem.sfd[i].sfdVec[j].name<<"  "<<fileSystem.sfd[i].sfdVec[j].id<<"  ";
            }
        }
    }

    fclose(stdout);
    freopen("CON", "w", stdout);
}

/**
 * �˳�ǰ������̿�����
 * @param diskBlock
 * @param fileSystem
 * @return
 */
void exitDiskBlock(int* diskBlock, FileSystem fileSystem){

    //д�ش��̿�����
    freopen("diskBlock.txt", "w", stdout);
    for (int i = 0; i < 512; i++){
        if (!diskBlock[i]){
            printf("  %d ", fileSystem.diskBlock[i].strNum);  //�ļ�ռ�ô��̿����
            /*cout<<fileSystem.diskBlock[i].strNum;
            string str;
            for (int j = 0; j < fileSystem.diskBlock[i].file.size(); j++){
                if (fileSystem.diskBlock[i].file[j] == ' ' && str.size() == 0)
                    continue;
                else if (fileSystem.diskBlock[i].file[j] == ' '){
                    cout << " " << str << " ";  //�ļ�����
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
 * �˳�ǰ����i�ڵ�����
 * @param iNode
 * @param fileSystem
 */
void exitINode(int* iNode, FileSystem fileSystem){

    //д��i�������
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
 * �˳�ǰ���泬��������
 * @param fileSystem
 * @param diskBlock
 */
void exitSuperBlock(FileSystem fileSystem, int* diskBlock){

    //д�س���������
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
 * �˳�ϵͳ
 * @param fileSystem
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 */
void exitSystem(FileSystem fileSystem, int* iNode, int* SFDBlock, int* diskBlock){
    MessageBox(NULL, TEXT("��ӭ���ٴ�ʹ�ã�"), TEXT("HELLO"), MB_OK);
    exitSFD(SFDBlock, fileSystem);
    exitDiskBlock(diskBlock, fileSystem);
    exitINode(iNode, fileSystem);
    exitSuperBlock(fileSystem, diskBlock);
}