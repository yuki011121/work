// 文件的创建与删除模块
//int iNode[INODE_NUM] = { 0 };         	//i结点位势图，0表示占据，1表示空闲
//int diskBlock[DISK_NUM] = { 0 };     	//磁盘块位势图，0表示占据，1表示空闲
//int SFDBlock[SFD_NUM] = { 0 };      	//目录位势图，0表示占据，1表示空闲
//iaddr -1空闲

#include "FILE.h"

/**
 * 创建文件的第一个索引块
 * @param fileSystem 文件系统结构
 * @param diskBlock 
 * @return
 */
int createFirstIndexB(FileSystem* fileSystem, int* diskBlock){
    int num, iaddr[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; //num用于保存分配到的磁盘块号  iaddr[13]保存索引块中存储的索引项

    num = allocateOneBlock(fileSystem, diskBlock); //从文件系统中分配一个空闲磁盘块，返回分配到的磁盘块号。
    if (num < 0) {
        cout << "磁盘块已满，分配失败" << endl;
        return -1;
    }
    //(*fileSystem).diskBlock[num].strNum = 13;
    for (int i = 0; i < 13; i++){//将每个索引项转换为字符串，保存在 fileSystem 对应的磁盘块中的 file 字符串中。
        stringstream ss;
        string tmp;
        ss << iaddr[i];
        ss >> tmp;
        (*fileSystem).diskBlock[num].file = (*fileSystem).diskBlock[num].file + " " + tmp ;
    }
    (*fileSystem).diskBlock[num].strNum = (*fileSystem).diskBlock[num].file.size();//更新磁盘块中 strNum 字段的值，表示该磁盘块占用的字符串长度。
    return num;
}

/**
 * 为新创建的文件分配一个i结点
 * @param fileSystem
 * @param iNode
 * @param user
 * @param diskBlock
 * @param SFDBlock
 * @return
 */
int createiNode(FileSystem* fileSystem, int* iNode, string user, int* diskBlock, int* SFDBlock){

    int EBcount, inodeNo, indexnum;
    EBcount = (*fileSystem).superBlock.freeDisk;  //空闲磁盘块数
    if (EBcount == 0){
        setFontColor(12);
        cout << "无空闲磁盘块\n";
        return -1;
    }
    else if ((*fileSystem).superBlock.freei_node == 0){   //有没有空闲i结点
        setFontColor(12);
        cout << "无空闲i结点\n";
        return -1;
    }
    else{

        indexnum = createFirstIndexB(fileSystem, diskBlock);  //创建第一个索引块
        if (indexnum < 0)//创建索引块失败
            return -1;
        (*fileSystem).superBlock.freei_node--;
        inodeNo = (*fileSystem).superBlock.freeiid[0];   //空闲i结点数组,将新分配的 i 结点号对应的数组元素初始化为 0。
        vector<int>::iterator iter = (*fileSystem).superBlock.freeiid.begin();//iterator 则是 vector<int> 类型的迭代器，遍历元素。调用 freeiid 容器的成员函数 begin()，它返回指向容器中第一个元素的迭代器。
        iter = (*fileSystem).superBlock.freeiid.erase(iter);//删除 iter 指向的元素，iter 将指向被删除元素的下一个元素。
        iNode[inodeNo] = 0;//0占用

        createInitINode(inodeNo, 0, 0, fileSystem, user, iNode, SFDBlock);    //为创建文件或目录初始化i结点，类型为0，表示文件，长度为0，初始化i结点

        int master = checkUser(user);
        for (int i = 0; i < 8; i++)       
            (*fileSystem).iNode[inodeNo].auth[i] = 0;
        //只有当前用户可以有权限去创建，初始化权限
        (*fileSystem).iNode[inodeNo].auth[master - 1] = 1;//将当前用户的权限位设置为 1，表示该用户对该文件拥有权限。
        (*fileSystem).iNode[inodeNo].diskBlockNum = 1; //设置 i 结点的磁盘块数为 1
        (*fileSystem).iNode[inodeNo].diskBlockId = indexnum;//将第一个索引块的编号赋值给 i 结点的 diskBlockId 属性
        return inodeNo;
    }
    return -1;//创建失败
}

/**
 * 查询当前目录下一固定名的文件下标
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
 * 创建文件
 * @param name
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param user
 * @param diskBlock
 * @param SFDBlock磁盘块索引节点
 * @return
 */
int createFile(string name, FileSystem* fileSystem, int cur_SFD, int* iNode, string user, int* diskBlock, int* SFDBlock){
    SingleSFD tempSFD;
    int pos = checkExitsfd(name, *fileSystem, cur_SFD);//检查当前目录下是否已存在同名文件
    if (pos != -1){
        setFontColor(12);
        cout << "文件名冲突！\n";
        return 0;
    }
    else{
        int inodeNo = createiNode(fileSystem, iNode, user, diskBlock, SFDBlock);
        if (inodeNo == -1){
            setFontColor(12);
            cout << "空闲i结点不足，创建文件失败！\n";
            return 0;
        }
        else {//将新创建的文件的信息存储在临时目录项对象 tempSFD 中，包括 i 结点号、删除标志和文件名。
            tempSFD.id = inodeNo;
            tempSFD.delink = 1;
            tempSFD.name = name;
            (*fileSystem).sfd[cur_SFD].sfdVec.push_back(tempSFD);
            (*fileSystem).sfd[cur_SFD].sfdNum++;
            setFontColor(10);
            cout << "创建成功！\n";
        }
    }
    return 1;
}

/**
 * 删除指定名字的文件
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
    vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin();//获取当前目录的目录项向量的迭代器。
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){//查找与指定文件名匹配的目录项的位置 pos
        if ((*fileSystem).sfd[cur_SFD].sfdVec[i].name == name){
            pos = i;
            break;
        }
        iter++;
    }
    if (pos == -1){
        setFontColor(12);
        cout << "删除失败，不存在的文件名！\n";
        return 0;
    }
    else{//获取要删除文件的 i 结点号 inodeNo

        int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;
        if ((master = (*fileSystem).iNode[inodeNo].id) == checkUser(user)){ //i结点所对应的用户
            if ((*fileSystem).iNode[inodeNo].qcount > 1){ 
                int l = (*fileSystem).sfd[cur_SFD].sfdVec[pos].delink;
                if (l == 1) { //被链接
                    setFontColor(12);
                    cout << "存在链接文件，将级联删除" << endl;
                    findSinglesfd(inodeNo, fileSystem, cur_SFD);            //将级联删除共享目录
                    deleteINode(pos, fileSystem, cur_SFD, iNode, diskBlock, SFDBlock); //删除对应的 i 结点及其指向的磁盘块。
                    iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //回收sdf
                    (*fileSystem).sfd[cur_SFD].sfdNum--;//更新目录项数目
                }
                else if(!l) {
                    iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //回收sdf
                    (*fileSystem).sfd[cur_SFD].sfdNum--;
                    (*fileSystem).iNode[inodeNo].qcount--;
                }
            }
            else{
                deleteINode(pos, fileSystem, cur_SFD, iNode, diskBlock, SFDBlock);
                iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //回收sdf
                (*fileSystem).sfd[cur_SFD].sfdNum--;
            }

        }
    }
    return 1;
}
/**
 * 删除待删除文件对应的i结点及其指向的磁盘块
 * @param pos
 * @param fileSystem
 * @param cur_SFD
 * @param iNode
 * @param diskBlock
 * @param SFDBlock传递指向磁盘块索引节点（SFD）的数组的指针
 */
void deleteINode(int pos, FileSystem* fileSystem, int cur_SFD,
                 int* iNode, int* diskBlock, int* SFDBlock){
    int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;  //文件对应的i节点
    int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;  //所占磁盘块的id号的索引块
    int *iaddr = getIaddr(indexnum, *fileSystem);   //获取索引块的 iaddr 数组。
    for (int i = 0; i < 10; i++){
        if (iaddr[i] != -1)
            freeABlock(iaddr[i], diskBlock, fileSystem, SFDBlock);//释放占用的磁盘块
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
        freeABlock(iaddr[i], diskBlock, fileSystem, SFDBlock);   //回收索引块所对应的文件内容
    }
    freeABlock(indexnum, diskBlock, fileSystem, SFDBlock);       //回收索引块
    iNode[inodeNo] = 1;         //1表示空闲
    (*fileSystem).superBlock.freei_node++;  //回收i结点
    (*fileSystem).superBlock.freeiid.push_back(inodeNo);
}
/**
 * 遍历删除与待删除文件共享的文件目录
 * @param inodeNo
 * @param fileSystem
 * @param cur_SFD
 */
void findSinglesfd(int inodeNo, FileSystem* fileSystem, int cur_SFD){
    int flag = 0;
    for (int k = 0; k < SFD_NUM; k++){      //遍历文件系统中的所有 SFD 块。
        vector<SingleSFD>::iterator iter = (*fileSystem).sfd[k].sfdVec.begin(); //512个SFDblock
        for (int i = 0; i < (*fileSystem).sfd[k].sfdVec.size(); i++){
            if ((*fileSystem).sfd[k].sfdVec[i].id == inodeNo){//在每个 SFD 块的目录项向量中查找与待删除文件具有相同 i 结点号的目录项
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