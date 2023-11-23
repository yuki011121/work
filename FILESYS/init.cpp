// ��ʼ��ģ��

#include "FILE.h"


/**
 * @brief ��ʼ��������
 *
 * @param fileSystem
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 */
void initSuperBlock(FileSystem* fileSystem, int* iNode, int* SFDBlock, int* diskBlock) {
    freopen("superBlock.txt", "r", stdin);
    scanf("%d%d", &(*fileSystem).superBlock.i_node, &(*fileSystem).superBlock.freei_node);// i_node���� �� freei_node������
    for (int i = 0; i < (*fileSystem).superBlock.freei_node; i++) {
        int tmp;
        scanf("%d", &tmp);
        iNode[tmp] = 1;      //i���λʾͼ
        (*fileSystem).superBlock.freeiid.push_back(tmp);
    }
    scanf("%d%d", &(*fileSystem).superBlock.sfd, &(*fileSystem).superBlock.free_SFD);// SFD��Ŀ¼�ļ����������Ϳ��� SFD ��������
    for (int i = 0; i < (*fileSystem).superBlock.free_SFD; i++) {
        int tmp;
        scanf("%d", &tmp);
        SFDBlock[tmp] = 1;      //����SFD��Ŀ¼����ʼ��
        (*fileSystem).superBlock.freeSFD.push_back(tmp);
    }
    scanf("%d%d", &(*fileSystem).superBlock.disk, &(*fileSystem).superBlock.freeDisk);   //���̿�������Ϳ��д��̿������ 
    fclose(stdin);
    freopen("CON", "r", stdin);  //�ض�λ��׼����

    freopen("freeBlock.txt", "r", stdin);       //���еĴ��̿�������ӷ�����
    (*fileSystem).superBlock.freeDiskSta[0] = 1;     //����ĵ�һ��Ԫ������Ϊ 1����ʾ����һ��
    (*fileSystem).superBlock.freeDiskSta[1] = DISK_NUM;   //DISK_NUM ��ʾ���̿����������ʾ�������ӷ��ĵ�һ��
    for (int i = 2; i < BLOCK_NUM + 1; i++)
        (*fileSystem).superBlock.freeDiskSta[i] = 0; //��������� freeDiskSta �����е�ʣ��Ԫ��ȫ����ʼ��Ϊ 0��
    for (int i = 0; i < (*fileSystem).superBlock.freeDisk; i++) {
        int tmp;
        scanf("%d", &tmp);
        diskBlock[tmp] = 1;                               //1��ʾ���У����̿�λʾͼ��ʼ��
        int& pos = (*fileSystem).superBlock.freeDiskSta[0];  //ÿ�ζ�����λʾͼջ������ջ����Ŀǰ�ÿ��д�ŵĿ��п���
        if (pos < BLOCK_NUM)
            (*fileSystem).superBlock.freeDiskSta[++pos] = tmp;    //���ÿ��п�
        else {   //�����鴦��
            .
            for (int i = 0; i <= BLOCK_NUM; i++) {
                stringstream ss;
                string tmpstr;//����ֵת��Ϊ�ַ�����������洢�� tmpstr ����
                ss << (*fileSystem).superBlock.freeDiskSta[i];
                ss >> tmpstr;
                (*fileSystem).diskBlock[tmp].file += " ";
                (*fileSystem).diskBlock[tmp].file += tmpstr;
            }
            (*fileSystem).diskBlock[tmp].strNum = -1; //����Ϊ�鳤��
            (*fileSystem).superBlock.freeDiskSta[0] = 1;
            (*fileSystem).superBlock.freeDiskSta[1] = tmp;//tmp ��֮ǰ�������鳤��������š�
            for (int i = 2; i < BLOCK_NUM + 1; i++)//�½��鳤��
                (*fileSystem).superBlock.freeDiskSta[i] = 0;//���������д����� 2 �� BLOCK_NUM + 1��Ϊ 0��
        }
    }
    fclose(stdin);
    freopen("CON", "r", stdin);//����׼������������Ϊ����̨����
}



/**
 * @brief ��ʼ��i���
 *
 * @param fileSystem
 * @param iNode
 */
void initINode(FileSystem* fileSystem, int* iNode) {
    //��ʼ����Ŀ¼���û�Ŀ¼
    freopen("iNode.txt", "r", stdin);
    for (int i = 0; i <= 8; i++) {
        scanf("%d%d%d%d%d", &(*fileSystem).iNode[i].id, &(*fileSystem).iNode[i].type,
            &(*fileSystem).iNode[i].sfd_id, &(*fileSystem).iNode[i].filelen, &(*fileSystem).iNode[i].qcount);
        (*fileSystem).iNode[i].diskBlockId = -1;
        (*fileSystem).iNode[i].diskBlockNum = -1;
        for (int j = 0; j < 8; j++)
            scanf("%d", &(*fileSystem).iNode[i].auth[j]);       //�û���Ȩ��
    }

    fclose(stdin);
    freopen("CON", "r", stdin);
    freopen("iNodeContext.txt", "r", stdin);

    for (int i = 9; i < INODE_NUM; i++) {
        if (!iNode[i]) { //��鵱ǰ�����ڵ��Ƿ�Ϊ�գ�ֵΪ 0������ʾ�������ڵ���á�
            scanf("%d%d%d%d%d", &(*fileSystem).iNode[i].id, &(*fileSystem).iNode[i].type, &(*fileSystem).iNode[i].sfd_id,
                &(*fileSystem).iNode[i].filelen, &(*fileSystem).iNode[i].qcount);
            for (int j = 0; j < 8; j++)
                scanf("%d", &(*fileSystem).iNode[i].auth[j]);
            if ((*fileSystem).iNode[i].type == 0) { //type=0->�ļ� 
                scanf("%d%d", &(*fileSystem).iNode[i].diskBlockNum, &(*fileSystem).iNode[i].diskBlockId);
            }
            else {
                (*fileSystem).iNode[i].diskBlockId = -1;
                (*fileSystem).iNode[i].diskBlockNum = -1;
            }
        }
        else {//�����ǰ�����ڵ��ѱ�ռ�ã�iNode[i] ��Ϊ 0�����򽫵�ǰ�����ڵ�ĸ��ֶζ���ʼ��Ϊ -1����ʾ�������ڵ���Ч��
            (*fileSystem).iNode[i].id = -1;
            (*fileSystem).iNode[i].type = -1;
            for (int j = 0; j < 8; j++)
                (*fileSystem).iNode[i].auth[j] = -1;
            (*fileSystem).iNode[i].diskBlockId = -1;
            (*fileSystem).iNode[i].diskBlockNum = -1;
            (*fileSystem).iNode[i].sfd_id = -1;
            (*fileSystem).iNode[i].filelen = -1;
            (*fileSystem).iNode[i].qcount = -1;
        }
    }

    fclose(stdin);
    freopen("CON", "r", stdin);
}

/**
 * @brief ��ʼ�����̿�
 *
 * @param diskBlock
 * @param fileSystem
 */
void initDiskBlock(int* diskBlock, FileSystem* fileSystem){
    freopen("diskBlock.txt", "r", stdin);
    char ch = '\0';//���ڴ洢���ļ��ж�ȡ���ַ���
    for (int i = 0; i < DISK_NUM; i++) {
        if (!diskBlock[i]) {//��鵱ǰ���̿��Ƿ�Ϊ�գ�ֵΪ 0������ʾ�ô��̿���á�
            scanf("%d", &(*fileSystem).diskBlock[i].strNum);
            getchar();//���ո�
            for (int j = 0; j < (*fileSystem).diskBlock[i].strNum; j++) {
                ch = getchar();
                (*fileSystem).diskBlock[i].file += ch;
            }
        }
        else if ((*fileSystem).diskBlock[i].strNum != -1) {//���ĳ�����̿��ѱ�ռ������ strNum ���Բ�Ϊ -1��˵���ô��̿�ԭ���洢������
            (*fileSystem).diskBlock[i].file = "";//�򽫵�ǰ���̿�� file �ַ����� strNum ���Զ���ʼ��Ϊ��ʼ״̬��
            (*fileSystem).diskBlock[i].strNum = 0;
        }
    }
    fclose(stdin);
    freopen("CON", "r", stdin);
}

/**
 * @brief ��ʼ��SFD
 *
 * @param fileSystem
 * @param staSFD
 * @param SFDBlock
 */
void initSFD(FileSystem* fileSystem, stack<int>* staSFD, int* SFDBlock){
//��ʼ��SFD
    freopen("sfdContext.txt", "r", stdin);
    (*fileSystem).sfd[0].sfdNum = 8;//��ʼ����Ŀ¼�� SFD������Ŀ¼�� sfdNum ��������Ϊ 8
    for (int i = 1; i <= 8; i++){		//�޸�
        string tmps;
        stringstream ss;
        ss << i;
        ss >> tmps;
        SingleSFD singleSFD; //����һ�� SingleSFD �ṹ����� singleSFD
        singleSFD.name = "root" + tmps;
        singleSFD.id = i;
        (*fileSystem).sfd[0].sfdVec.push_back(singleSFD);   //����ǰSFD��ӵ���Ŀ¼��SFD�����С�ÿ���ļ�Ŀ¼�µ�sfd��̬����
    }

    (*staSFD).push(0);    //��¼Ŀ¼ջ

    for (int i = 1; i < SFD_NUM; i++){

        if (!SFDBlock[i]){       //����ǰSFD���ã�����ļ��ж�ȡ sfdNum �ֶε�ֵ��������洢����ǰSFD�� sfdNum �ֶ��С�            ֻҪSFDBlock������
            scanf("%d", &(*fileSystem).sfd[i].sfdNum);
            //cin>>fileSystem.sfd[i].sfdNum;
            for (int j = 0; j < (*fileSystem).sfd[i].sfdNum; j++){
                SingleSFD singleSFD;
                cin >> singleSFD.name;
                scanf("%d%d", &singleSFD.id, &singleSFD.delink);     //�ļ���Ӧi�����
                (*fileSystem).sfd[i].sfdVec.push_back(singleSFD);
            }
        }
        else {
            (*fileSystem).sfd[i].sfdNum = 0; //�����ǰSFD�ѱ�ռ�� 
        }
    }

    fclose(stdin);
    freopen("CON", "r", stdin);
}

/**
 * @brief ��ʼ���ļ�ϵͳ
 *
 * @param iNode
 * @param diskBlock
 * @param SFDBlock
 * @param fileSystem
 * @param staSFD
 */
void initFileSystem(int* iNode, int* diskBlock, int* SFDBlock, FileSystem* fileSystem, stack<int>* staSFD){
    fileSystem->boot = 0;
    initSuperBlock(fileSystem, iNode, SFDBlock, diskBlock);  //��ʼ��ʱ��ſ�ʼ�ѿ��е���Ϊ1
    initINode(fileSystem, iNode);
    initDiskBlock(diskBlock, fileSystem);
    initSFD(fileSystem, staSFD, SFDBlock);
}
/**
 * ��ʼ��ϵͳ���ļ��б�
 * @param sysOpenFile
 */
void initOpenFileList(SysOpenFile* sysOpenFile){
    for(int i = 0;i < SYSOPENFILE;i++){
        sysOpenFile[i].count = 0;
        sysOpenFile[i].id = -1;
        sysOpenFile[i].iId = -1;
    }
}