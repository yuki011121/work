// �ļ��Ĵ�����ɾ��ģ��
//int iNode[INODE_NUM] = { 0 };         	//i���λ��ͼ��0��ʾռ�ݣ�1��ʾ����
//int diskBlock[DISK_NUM] = { 0 };     	//���̿�λ��ͼ��0��ʾռ�ݣ�1��ʾ����
//int SFDBlock[SFD_NUM] = { 0 };      	//Ŀ¼λ��ͼ��0��ʾռ�ݣ�1��ʾ����
//iaddr -1����

#include "FILE.h"

/**
 * �����ļ��ĵ�һ��������
 * @param fileSystem �ļ�ϵͳ�ṹ
 * @param diskBlock 
 * @return
 */
int createFirstIndexB(FileSystem* fileSystem, int* diskBlock){
    int num, iaddr[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; //num���ڱ�����䵽�Ĵ��̿��  iaddr[13]�����������д洢��������

    num = allocateOneBlock(fileSystem, diskBlock); //���ļ�ϵͳ�з���һ�����д��̿飬���ط��䵽�Ĵ��̿�š�
    if (num < 0) {
        cout << "���̿�����������ʧ��" << endl;
        return -1;
    }
    //(*fileSystem).diskBlock[num].strNum = 13;
    for (int i = 0; i < 13; i++){//��ÿ��������ת��Ϊ�ַ����������� fileSystem ��Ӧ�Ĵ��̿��е� file �ַ����С�
        stringstream ss;
        string tmp;
        ss << iaddr[i];
        ss >> tmp;
        (*fileSystem).diskBlock[num].file = (*fileSystem).diskBlock[num].file + " " + tmp ;
    }
    (*fileSystem).diskBlock[num].strNum = (*fileSystem).diskBlock[num].file.size();//���´��̿��� strNum �ֶε�ֵ����ʾ�ô��̿�ռ�õ��ַ������ȡ�
    return num;
}

/**
 * Ϊ�´������ļ�����һ��i���
 * @param fileSystem
 * @param iNode
 * @param user
 * @param diskBlock
 * @param SFDBlock
 * @return
 */
int createiNode(FileSystem* fileSystem, int* iNode, string user, int* diskBlock, int* SFDBlock){

    int EBcount, inodeNo, indexnum;
    EBcount = (*fileSystem).superBlock.freeDisk;  //���д��̿���
    if (EBcount == 0){
        setFontColor(12);
        cout << "�޿��д��̿�\n";
        return -1;
    }
    else if ((*fileSystem).superBlock.freei_node == 0){   //��û�п���i���
        setFontColor(12);
        cout << "�޿���i���\n";
        return -1;
    }
    else{

        indexnum = createFirstIndexB(fileSystem, diskBlock);  //������һ��������
        if (indexnum < 0)//����������ʧ��
            return -1;
        (*fileSystem).superBlock.freei_node--;
        inodeNo = (*fileSystem).superBlock.freeiid[0];   //����i�������,���·���� i ���Ŷ�Ӧ������Ԫ�س�ʼ��Ϊ 0��
        vector<int>::iterator iter = (*fileSystem).superBlock.freeiid.begin();//iterator ���� vector<int> ���͵ĵ�����������Ԫ�ء����� freeiid �����ĳ�Ա���� begin()��������ָ�������е�һ��Ԫ�صĵ�������
        iter = (*fileSystem).superBlock.freeiid.erase(iter);//ɾ�� iter ָ���Ԫ�أ�iter ��ָ��ɾ��Ԫ�ص���һ��Ԫ�ء�
        iNode[inodeNo] = 0;//0ռ��

        createInitINode(inodeNo, 0, 0, fileSystem, user, iNode, SFDBlock);    //Ϊ�����ļ���Ŀ¼��ʼ��i��㣬����Ϊ0����ʾ�ļ�������Ϊ0����ʼ��i���

        int master = checkUser(user);
        for (int i = 0; i < 8; i++)       
            (*fileSystem).iNode[inodeNo].auth[i] = 0;
        //ֻ�е�ǰ�û�������Ȩ��ȥ��������ʼ��Ȩ��
        (*fileSystem).iNode[inodeNo].auth[master - 1] = 1;//����ǰ�û���Ȩ��λ����Ϊ 1����ʾ���û��Ը��ļ�ӵ��Ȩ�ޡ�
        (*fileSystem).iNode[inodeNo].diskBlockNum = 1; //���� i ���Ĵ��̿���Ϊ 1
        (*fileSystem).iNode[inodeNo].diskBlockId = indexnum;//����һ��������ı�Ÿ�ֵ�� i ���� diskBlockId ����
        return inodeNo;
    }
    return -1;//����ʧ��
}

/**
 * ��ѯ��ǰĿ¼��һ�̶������ļ��±�
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @return
 */
int checkExitsfd(string name, FileSystem fileSystem, int cur_SFD){
    int pos = -1;
    for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
        if (fileSystem.sfd[cur_SFD].sfdVec[i].name == name){
            pos = i;
            break;
        }
    }
    return pos;
}
/**
 * �����ļ�
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param user
 * @param diskBlock
 * @param SFDBlock���̿������ڵ�
 * @return
 */
int createFile(string name, FileSystem* fileSystem, int cur_SFD, int* iNode, string user, int* diskBlock, int* SFDBlock){
    SingleSFD tempSFD;
    int pos = checkExitsfd(name, *fileSystem, cur_SFD);//��鵱ǰĿ¼���Ƿ��Ѵ���ͬ���ļ�
    if (pos != -1){
        setFontColor(12);
        cout << "�ļ�����ͻ��\n";
        return 0;
    }
    else{
        int inodeNo = createiNode(fileSystem, iNode, user, diskBlock, SFDBlock);
        if (inodeNo == -1){
            setFontColor(12);
            cout << "����i��㲻�㣬�����ļ�ʧ�ܣ�\n";
            return 0;
        }
        else {//���´������ļ�����Ϣ�洢����ʱĿ¼����� tempSFD �У����� i ���š�ɾ����־���ļ�����
            tempSFD.id = inodeNo;
            tempSFD.delink = 1;
            tempSFD.name = name;
            (*fileSystem).sfd[cur_SFD].sfdVec.push_back(tempSFD);
            (*fileSystem).sfd[cur_SFD].sfdNum++;
            setFontColor(10);
            cout << "�����ɹ���\n";
        }
    }
    return 1;
}

/**
 * ɾ��ָ�����ֵ��ļ�
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param iNode
 * @param diskBlock
 * @param SFDBlock
 * @return
 */
int freeFile(string name, FileSystem* fileSystem, int cur_SFD, string user, int* iNode, int* diskBlock, int* SFDBlock){
    int pos = -1;
    int master;
    vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin();//��ȡ��ǰĿ¼��Ŀ¼�������ĵ�������
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){//������ָ���ļ���ƥ���Ŀ¼���λ�� pos
        if ((*fileSystem).sfd[cur_SFD].sfdVec[i].name == name){
            pos = i;
            break;
        }
        iter++;
    }
    if (pos == -1){
        setFontColor(12);
        cout << "ɾ��ʧ�ܣ������ڵ��ļ�����\n";
        return 0;
    }
    else{//��ȡҪɾ���ļ��� i ���� inodeNo

        int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;
        if ((master = (*fileSystem).iNode[inodeNo].id) == checkUser(user)){ //i�������Ӧ���û�
            if ((*fileSystem).iNode[inodeNo].qcount > 1){ 
                int l = (*fileSystem).sfd[cur_SFD].sfdVec[pos].delink;
                if (l == 1) { //������
                    setFontColor(12);
                    cout << "���������ļ���������ɾ��" << endl;
                    findSinglesfd(inodeNo, fileSystem, cur_SFD);            //������ɾ������Ŀ¼
                    deleteINode(pos, fileSystem, cur_SFD, iNode, diskBlock, SFDBlock); //ɾ����Ӧ�� i ��㼰��ָ��Ĵ��̿顣
                    iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //����sdf
                    (*fileSystem).sfd[cur_SFD].sfdNum--;//����Ŀ¼����Ŀ
                }
                else if(!l) {
                    iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //����sdf
                    (*fileSystem).sfd[cur_SFD].sfdNum--;
                    (*fileSystem).iNode[inodeNo].qcount--;
                }
            }
            else{
                deleteINode(pos, fileSystem, cur_SFD, iNode, diskBlock, SFDBlock);
                iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //����sdf
                (*fileSystem).sfd[cur_SFD].sfdNum--;
            }

        }
    }
    return 1;
}
/**
 * ɾ����ɾ���ļ���Ӧ��i��㼰��ָ��Ĵ��̿�
 * @param pos
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param diskBlock
 * @param SFDBlock����ָ����̿������ڵ㣨SFD���������ָ��
 */
void deleteINode(int pos, FileSystem* fileSystem, int cur_SFD,
                 int* iNode, int* diskBlock, int* SFDBlock){
    int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;  //�ļ���Ӧ��i�ڵ�
    int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;  //��ռ���̿��id�ŵ�������
    int *iaddr = getIaddr(indexnum, *fileSystem);   //��ȡ������� iaddr ���顣
    for (int i = 0; i < 10; i++){
        if (iaddr[i] != -1)
            freeABlock(iaddr[i], diskBlock, fileSystem, SFDBlock);//�ͷ�ռ�õĴ��̿�
    }
    for (int i = 10; i < 13; i++){
        if (iaddr[i] == -1)
            break;
        int *iaddr_1 = getIaddr(iaddr[i], *fileSystem);
        for (int j = 0; j < 128; j++){
            if (iaddr_1[j] != -1)
                freeABlock(iaddr_1[j], diskBlock, fileSystem, SFDBlock);
            else
                break;
        }
        freeABlock(iaddr[i], diskBlock, fileSystem, SFDBlock);   //��������������Ӧ���ļ�����
    }
    freeABlock(indexnum, diskBlock, fileSystem, SFDBlock);       //����������
    iNode[inodeNo] = 1;         //1��ʾ����
    (*fileSystem).superBlock.freei_node++;  //����i���
    (*fileSystem).superBlock.freeiid.push_back(inodeNo);
}
/**
 * ����ɾ�����ɾ���ļ�������ļ�Ŀ¼
 * @param inodeNo
 * @param fileSystem
 * @param cur_SFD
 */
void findSinglesfd(int inodeNo, FileSystem* fileSystem, int cur_SFD){
    int flag = 0;
    for (int k = 0; k < SFD_NUM; k++){      //�����ļ�ϵͳ�е����� SFD �顣
        vector<SingleSFD>::iterator iter = (*fileSystem).sfd[k].sfdVec.begin(); //512��SFDblock
        for (int i = 0; i < (*fileSystem).sfd[k].sfdVec.size(); i++){
            if ((*fileSystem).sfd[k].sfdVec[i].id == inodeNo){//��ÿ�� SFD ���Ŀ¼�������в������ɾ���ļ�������ͬ i ���ŵ�Ŀ¼��
                flag = 1;
                break;
            }
            iter++;
        }
        if (flag == 1 && k != cur_SFD){
            iter = (*fileSystem).sfd[k].sfdVec.erase(iter);
            (*fileSystem).sfd[k].sfdNum--;
        }
        flag = 0;
    }
}