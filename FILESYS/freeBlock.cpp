// ���д��̿�������ģ��
#include "FILE.h"

/**
 * ��װ����ջ����д��һ���ض����̿�
 * @param r
 * @param fileSystem
 */
void writeABlock(int r, FileSystem* fileSystem) {   //����ʱջ��
    for (int i = 0; i <= BLOCK_NUM; i++) {
        stringstream ss;
        string str;
        ss << (*fileSystem).superBlock.freeDiskSta[i];   //���������ӷ����д��̿�ջ[i]�д�ŵ������Ǹ�����д��̿���
        ss >> str;
        (*fileSystem).diskBlock[r].file = (*fileSystem).diskBlock[r].file + "  " + str;    //��������д��̿��Ŵ����ض��Ĵ��̿�
        (*fileSystem).diskBlock[r].strNum++;    //���ض��Ĵ��̿����ļ����ݳ��ȼ�һ�������˿�ţ�
    }
}
/**
 * ��һ��д�ſ��д��̿�ŵĴ��̿�����д��ջ
 * @param r
 * @param fileSystem
 */
void readABlock(int r, FileSystem* fileSystem) {   //����ʱջ��
    int tmp = 0, f = -1, pos = 0;
    for (int i = 0; i < (*fileSystem).diskBlock[r].file.size(); i++) {
        if ((*fileSystem).diskBlock[r].file[i] == ' ' && f == -1)
            continue;
        else if ((*fileSystem).diskBlock[r].file[i] == ' ') {
            (*fileSystem).superBlock.freeDiskSta[pos++] = tmp;//���鳤���е�����д����д��̿�ջ
            tmp = 0;
            f = -1;
        }
        else {
            tmp = tmp * 10 + (*fileSystem).diskBlock[r].file[i] - '0';    //�����̿����ַ�������ת��Ϊ��
            f = 1;
        }
    }
    (*fileSystem).superBlock.freeDiskSta[pos] = tmp;    //�鳤�������һ�����ݶ���
    (*fileSystem).diskBlock[r].file = "";    //��ո��鳤��
    (*fileSystem).diskBlock[r].strNum = 0;
}
/**
 * �ڳ��������л���һ�����д��̿�
 * @param BlockNo
 * @param diskBlock
 * @param fileSystem
 * @param SFDBlock
 */
void freeABlock(int BlockNo, int* diskBlock, FileSystem* fileSystem, int* SFDBlock) {//�ȷ���ĺ����
    int r;
    diskBlock[BlockNo] = 1;       //�޸�λʾͼ
    (*fileSystem).diskBlock[BlockNo].file = "";  //��ոô��̿�����
    (*fileSystem).diskBlock[BlockNo].strNum = 0;
    if ((*fileSystem).superBlock.freeDiskSta[0] == BLOCK_NUM) {  //���������п��д���ջ����ϢΪ5˵��ջ����
        writeABlock(BlockNo, fileSystem);    //��ջ����Ϣ����û��յĿ��п��У�ʹ���п��Ϊ��һ����鳤��
        (*fileSystem).superBlock.freeDiskSta[0] = 1;    //�����д��̿�ջ��ջ��Ԫ����Ϊ1
        (*fileSystem).superBlock.freeDiskSta[1] = BlockNo;   //�����鳤��ĵ�ַ������д��̿�ջ�Ĵ�ջ��
        for (int i = 2; i < BLOCK_NUM + 1; i++)
            (*fileSystem).superBlock.freeDiskSta[i] = 0;    //ջ������λ�ó�ʼ��Ϊ0
    }
    else {
        (*fileSystem).superBlock.freeDiskSta[0]++;    //��ջ��Ԫ�ز�Ϊ5��ջδ����ջ��Ԫ�ؼ�һ
        r = (*fileSystem).superBlock.freeDiskSta[0];
        (*fileSystem).superBlock.freeDiskSta[r] = BlockNo;    //���ô��̿�λ�ô���ջ��

    }

    (*fileSystem).superBlock.freeDisk++;    //�������м�¼�Ŀ��д��̿�����һ
    //SFDBlock[r] = 1;          //Ŀ¼λʾͼ
}
/**
 * �ڳ��������з���һ�����д��̿�
 * @param fileSystem
 * @param diskBlock
 * @return
 */
int allocateOneBlock(FileSystem* fileSystem, int* diskBlock) {    //����ʧ�ܷ���-1���ɹ��򷵻ط���Ŀ��д��̿���
    int r, mid;
    if ((*fileSystem).superBlock.freeDiskSta[0] == 1) {    //�������п��д���ջ��ջ��Ԫ��Ϊ1
        if ((*fileSystem).superBlock.freeDiskSta[1] == DISK_NUM) {    //����ջ��Ԫ��Ϊ512˵�����п��Ѿ��������
            setFontColor(12);
            cout << "���д��̿����ʧ��";
            return -1;
        }
        else {
            r = (*fileSystem).superBlock.freeDiskSta[1];    //������䵽���鳤�飬��Ҫ���鳤����Ϣ������д���ջ�У��ٽ��ÿ����
            readABlock(r, fileSystem);
            (*fileSystem).superBlock.freeDisk--;    //�������м�¼�Ŀ��д��̿�����һ
        }
    }
    else {
        mid = (*fileSystem).superBlock.freeDiskSta[0];    //�������п��д���ջջ��Ԫ�ظ�����ջ�ף�
        r = (*fileSystem).superBlock.freeDiskSta[mid];    //ջ����ŵ��Ǵ�����Ĵ��̿���
        (*fileSystem).superBlock.freeDiskSta[mid] = 0;    //���������п��д���ջջ�����������ʾ�ѷ���
        (*fileSystem).superBlock.freeDiskSta[0]--;        //�������п��д���ջԪ�ظ�����һ
        (*fileSystem).superBlock.freeDisk--;              //�������м�¼�Ŀ��д��̿�����һ
    }
    diskBlock[r] = 0;    //��ʼ���÷���Ĵ��̿�
    return r;    //���ط���Ŀ��д��̿���
}