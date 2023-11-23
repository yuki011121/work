// 初始化模块

#include "FILE.h"


/**
 * @brief 初始化超级块
 *
 * @param fileSystem
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 */
void initSuperBlock(FileSystem* fileSystem, int* iNode, int* SFDBlock, int* diskBlock) {
    freopen("superBlock.txt", "r", stdin);
    scanf("%d%d", &(*fileSystem).superBlock.i_node, &(*fileSystem).superBlock.freei_node);// i_node总数 和 freei_node总数，
    for (int i = 0; i < (*fileSystem).superBlock.freei_node; i++) {
        int tmp;
        scanf("%d", &tmp);
        iNode[tmp] = 1;      //i结点位示图
        (*fileSystem).superBlock.freeiid.push_back(tmp);
    }
    scanf("%d%d", &(*fileSystem).superBlock.sfd, &(*fileSystem).superBlock.free_SFD);// SFD（目录文件）的总数和空闲 SFD 的数量。
    for (int i = 0; i < (*fileSystem).superBlock.free_SFD; i++) {
        int tmp;
        scanf("%d", &tmp);
        SFDBlock[tmp] = 1;      //空闲SFD（目录）初始化
        (*fileSystem).superBlock.freeSFD.push_back(tmp);
    }
    scanf("%d%d", &(*fileSystem).superBlock.disk, &(*fileSystem).superBlock.freeDisk);   //磁盘块的总数和空闲磁盘块的数量 
    fclose(stdin);
    freopen("CON", "r", stdin);  //重定位标准输入

    freopen("freeBlock.txt", "r", stdin);       //空闲的磁盘块成组链接法保存
    (*fileSystem).superBlock.freeDiskSta[0] = 1;     //数组的第一个元素设置为 1，表示已入一块
    (*fileSystem).superBlock.freeDiskSta[1] = DISK_NUM;   //DISK_NUM 表示磁盘块的总数，表示成组链接法的第一块
    for (int i = 2; i < BLOCK_NUM + 1; i++)
        (*fileSystem).superBlock.freeDiskSta[i] = 0; //将超级块的 freeDiskSta 数组中的剩余元素全部初始化为 0。
    for (int i = 0; i < (*fileSystem).superBlock.freeDisk; i++) {
        int tmp;
        scanf("%d", &tmp);
        diskBlock[tmp] = 1;                               //1表示空闲，磁盘块位示图初始化
        int& pos = (*fileSystem).superBlock.freeDiskSta[0];  //每次都等于位示图栈顶数（栈顶是目前该块中存放的空闲块数
        if (pos < BLOCK_NUM)
            (*fileSystem).superBlock.freeDiskSta[++pos] = tmp;    //放置空闲块
        else {   //超级块处理
            .
            for (int i = 0; i <= BLOCK_NUM; i++) {
                stringstream ss;
                string tmpstr;//整数值转换为字符串，并将其存储在 tmpstr 变量
                ss << (*fileSystem).superBlock.freeDiskSta[i];
                ss >> tmpstr;
                (*fileSystem).diskBlock[tmp].file += " ";
                (*fileSystem).diskBlock[tmp].file += tmpstr;
            }
            (*fileSystem).diskBlock[tmp].strNum = -1; //设置为组长块
            (*fileSystem).superBlock.freeDiskSta[0] = 1;
            (*fileSystem).superBlock.freeDiskSta[1] = tmp;//tmp 是之前创建的组长块的索引号。
            for (int i = 2; i < BLOCK_NUM + 1; i++)//新建组长块
                (*fileSystem).superBlock.freeDiskSta[i] = 0;//将超级块中从索引 2 到 BLOCK_NUM + 1置为 0，
        }
    }
    fclose(stdin);
    freopen("CON", "r", stdin);//将标准输入重新设置为控制台输入
}



/**
 * @brief 初始化i结点
 *
 * @param fileSystem
 * @param iNode
 */
void initINode(FileSystem* fileSystem, int* iNode) {
    //初始化根目录及用户目录
    freopen("iNode.txt", "r", stdin);
    for (int i = 0; i <= 8; i++) {
        scanf("%d%d%d%d%d", &(*fileSystem).iNode[i].id, &(*fileSystem).iNode[i].type,
            &(*fileSystem).iNode[i].sfd_id, &(*fileSystem).iNode[i].filelen, &(*fileSystem).iNode[i].qcount);
        (*fileSystem).iNode[i].diskBlockId = -1;
        (*fileSystem).iNode[i].diskBlockNum = -1;
        for (int j = 0; j < 8; j++)
            scanf("%d", &(*fileSystem).iNode[i].auth[j]);       //用户的权限
    }

    fclose(stdin);
    freopen("CON", "r", stdin);
    freopen("iNodeContext.txt", "r", stdin);

    for (int i = 9; i < INODE_NUM; i++) {
        if (!iNode[i]) { //检查当前索引节点是否为空（值为 0），表示该索引节点可用。
            scanf("%d%d%d%d%d", &(*fileSystem).iNode[i].id, &(*fileSystem).iNode[i].type, &(*fileSystem).iNode[i].sfd_id,
                &(*fileSystem).iNode[i].filelen, &(*fileSystem).iNode[i].qcount);
            for (int j = 0; j < 8; j++)
                scanf("%d", &(*fileSystem).iNode[i].auth[j]);
            if ((*fileSystem).iNode[i].type == 0) { //type=0->文件 
                scanf("%d%d", &(*fileSystem).iNode[i].diskBlockNum, &(*fileSystem).iNode[i].diskBlockId);
            }
            else {
                (*fileSystem).iNode[i].diskBlockId = -1;
                (*fileSystem).iNode[i].diskBlockNum = -1;
            }
        }
        else {//如果当前索引节点已被占用（iNode[i] 不为 0），则将当前索引节点的各字段都初始化为 -1，表示该索引节点无效。
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
 * @brief 初始化磁盘块
 *
 * @param diskBlock
 * @param fileSystem
 */
void initDiskBlock(int* diskBlock, FileSystem* fileSystem){
    freopen("diskBlock.txt", "r", stdin);
    char ch = '\0';//用于存储从文件中读取的字符。
    for (int i = 0; i < DISK_NUM; i++) {
        if (!diskBlock[i]) {//检查当前磁盘块是否为空（值为 0），表示该磁盘块可用。
            scanf("%d", &(*fileSystem).diskBlock[i].strNum);
            getchar();//读空格
            for (int j = 0; j < (*fileSystem).diskBlock[i].strNum; j++) {
                ch = getchar();
                (*fileSystem).diskBlock[i].file += ch;
            }
        }
        else if ((*fileSystem).diskBlock[i].strNum != -1) {//如果某个磁盘块已被占用且其 strNum 属性不为 -1，说明该磁盘块原本存储了数据
            (*fileSystem).diskBlock[i].file = "";//则将当前磁盘块的 file 字符串和 strNum 属性都初始化为初始状态。
            (*fileSystem).diskBlock[i].strNum = 0;
        }
    }
    fclose(stdin);
    freopen("CON", "r", stdin);
}

/**
 * @brief 初始化SFD
 *
 * @param fileSystem
 * @param staSFD
 * @param SFDBlock
 */
void initSFD(FileSystem* fileSystem, stack<int>* staSFD, int* SFDBlock){
//初始化SFD
    freopen("sfdContext.txt", "r", stdin);
    (*fileSystem).sfd[0].sfdNum = 8;//初始化根目录的 SFD，将根目录的 sfdNum 属性设置为 8
    for (int i = 1; i <= 8; i++){		//修改
        string tmps;
        stringstream ss;
        ss << i;
        ss >> tmps;
        SingleSFD singleSFD; //创建一个 SingleSFD 结构体对象 singleSFD
        singleSFD.name = "root" + tmps;
        singleSFD.id = i;
        (*fileSystem).sfd[0].sfdVec.push_back(singleSFD);   //将当前SFD添加到根目录的SFD向量中。每个文件目录下的sfd动态数组
    }

    (*staSFD).push(0);    //记录目录栈

    for (int i = 1; i < SFD_NUM; i++){

        if (!SFDBlock[i]){       //果当前SFD可用，则从文件中读取 sfdNum 字段的值，并将其存储到当前SFD的 sfdNum 字段中。            只要SFDBlock不空闲
            scanf("%d", &(*fileSystem).sfd[i].sfdNum);
            //cin>>fileSystem.sfd[i].sfdNum;
            for (int j = 0; j < (*fileSystem).sfd[i].sfdNum; j++){
                SingleSFD singleSFD;
                cin >> singleSFD.name;
                scanf("%d%d", &singleSFD.id, &singleSFD.delink);     //文件对应i结点编号
                (*fileSystem).sfd[i].sfdVec.push_back(singleSFD);
            }
        }
        else {
            (*fileSystem).sfd[i].sfdNum = 0; //如果当前SFD已被占用 
        }
    }

    fclose(stdin);
    freopen("CON", "r", stdin);
}

/**
 * @brief 初始化文件系统
 *
 * @param iNode
 * @param diskBlock
 * @param SFDBlock
 * @param fileSystem
 * @param staSFD
 */
void initFileSystem(int* iNode, int* diskBlock, int* SFDBlock, FileSystem* fileSystem, stack<int>* staSFD){
    fileSystem->boot = 0;
    initSuperBlock(fileSystem, iNode, SFDBlock, diskBlock);  //初始化时候才开始把空闲的置为1
    initINode(fileSystem, iNode);
    initDiskBlock(diskBlock, fileSystem);
    initSFD(fileSystem, staSFD, SFDBlock);
}
/**
 * 初始化系统打开文件列表
 * @param sysOpenFile
 */
void initOpenFileList(SysOpenFile* sysOpenFile){
    for(int i = 0;i < SYSOPENFILE;i++){
        sysOpenFile[i].count = 0;
        sysOpenFile[i].id = -1;
        sysOpenFile[i].iId = -1;
    }
}