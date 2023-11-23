// 空闲磁盘块分配回收模块
#include "FILE.h"

/**
 * 将装满的栈内容写入一个特定磁盘块
 * @param r
 * @param fileSystem
 */
void writeABlock(int r, FileSystem* fileSystem) {   //回收时栈满
    for (int i = 0; i <= BLOCK_NUM; i++) {
        stringstream ss;
        string str;
        ss << (*fileSystem).superBlock.freeDiskSta[i];   //成组连链接法空闲磁盘块栈[i]中存放的内容是该组空闲磁盘块块号
        ss >> str;
        (*fileSystem).diskBlock[r].file = (*fileSystem).diskBlock[r].file + "  " + str;    //将该组空闲磁盘块块号存入特定的磁盘块
        (*fileSystem).diskBlock[r].strNum++;    //该特定的磁盘块中文件内容长度加一（增加了块号）
    }
}
/**
 * 将一个写着空闲磁盘块号的磁盘块内容写入栈
 * @param r
 * @param fileSystem
 */
void readABlock(int r, FileSystem* fileSystem) {   //分配时栈空
    int tmp = 0, f = -1, pos = 0;
    for (int i = 0; i < (*fileSystem).diskBlock[r].file.size(); i++) {
        if ((*fileSystem).diskBlock[r].file[i] == ' ' && f == -1)
            continue;
        else if ((*fileSystem).diskBlock[r].file[i] == ' ') {
            (*fileSystem).superBlock.freeDiskSta[pos++] = tmp;//将组长块中的内容写入空闲磁盘块栈
            tmp = 0;
            f = -1;
        }
        else {
            tmp = tmp * 10 + (*fileSystem).diskBlock[r].file[i] - '0';    //将磁盘块中字符型数字转化为数
            f = 1;
        }
    }
    (*fileSystem).superBlock.freeDiskSta[pos] = tmp;    //组长块中最后一个数据读入
    (*fileSystem).diskBlock[r].file = "";    //清空该组长块
    (*fileSystem).diskBlock[r].strNum = 0;
}
/**
 * 在成组链接中回收一个空闲磁盘块
 * @param BlockNo
 * @param diskBlock
 * @param fileSystem
 * @param SFDBlock
 */
void freeABlock(int BlockNo, int* diskBlock, FileSystem* fileSystem, int* SFDBlock) {//先分配的后回收
    int r;
    diskBlock[BlockNo] = 1;       //修改位示图
    (*fileSystem).diskBlock[BlockNo].file = "";  //清空该磁盘块内容
    (*fileSystem).diskBlock[BlockNo].strNum = 0;
    if ((*fileSystem).superBlock.freeDiskSta[0] == BLOCK_NUM) {  //若超级块中空闲磁盘栈中信息为5说明栈已满
        writeABlock(BlockNo, fileSystem);    //将栈中信息存入该回收的空闲块中，使空闲块成为新一组的组长块
        (*fileSystem).superBlock.freeDiskSta[0] = 1;    //将空闲磁盘块栈的栈底元素设为1
        (*fileSystem).superBlock.freeDiskSta[1] = BlockNo;   //将该组长块的地址存入空闲磁盘块栈的次栈底
        for (int i = 2; i < BLOCK_NUM + 1; i++)
            (*fileSystem).superBlock.freeDiskSta[i] = 0;    //栈中其他位置初始化为0
    }
    else {
        (*fileSystem).superBlock.freeDiskSta[0]++;    //若栈底元素不为5即栈未满，栈底元素加一
        r = (*fileSystem).superBlock.freeDiskSta[0];
        (*fileSystem).superBlock.freeDiskSta[r] = BlockNo;    //将该磁盘块位置存入栈中

    }

    (*fileSystem).superBlock.freeDisk++;    //超级块中记录的空闲磁盘块数加一
    //SFDBlock[r] = 1;          //目录位示图
}
/**
 * 在成组链接中分配一个空闲磁盘块
 * @param fileSystem
 * @param diskBlock
 * @return
 */
int allocateOneBlock(FileSystem* fileSystem, int* diskBlock) {    //分配失败返回-1，成功则返回分配的空闲磁盘块块号
    int r, mid;
    if ((*fileSystem).superBlock.freeDiskSta[0] == 1) {    //超级块中空闲磁盘栈的栈顶元素为1
        if ((*fileSystem).superBlock.freeDiskSta[1] == DISK_NUM) {    //若次栈顶元素为512说明空闲块已经分配完毕
            setFontColor(12);
            cout << "空闲磁盘块分配失败";
            return -1;
        }
        else {
            r = (*fileSystem).superBlock.freeDiskSta[1];    //否则分配到了组长块，需要将组长块信息存入空闲磁盘栈中，再将该块分配
            readABlock(r, fileSystem);
            (*fileSystem).superBlock.freeDisk--;    //超级块中记录的空闲磁盘块数减一
        }
    }
    else {
        mid = (*fileSystem).superBlock.freeDiskSta[0];    //超级块中空闲磁盘栈栈中元素个数（栈底）
        r = (*fileSystem).superBlock.freeDiskSta[mid];    //栈顶存放的是待分配的磁盘块块号
        (*fileSystem).superBlock.freeDiskSta[mid] = 0;    //将超级块中空闲磁盘栈栈顶内容清零表示已分配
        (*fileSystem).superBlock.freeDiskSta[0]--;        //超级块中空闲磁盘栈元素个数减一
        (*fileSystem).superBlock.freeDisk--;              //超级块中记录的空闲磁盘块数减一
    }
    diskBlock[r] = 0;    //初始化该分配的磁盘块
    return r;    //返回分配的空闲磁盘块块号
}