#include "FILE.h"

//为创建文件或目录初始化i结点
void createInitINode(int useINode, int type, int filelen, FileSystem* fileSystem, string user, int* iNode, int* SFDBlock){

	//新建目录或文件时初始化i结点
	(*fileSystem).iNode[useINode].id = checkUser(user);  //i结点所属用户
	(*fileSystem).iNode[useINode].type = type;     //文件类型
	(*fileSystem).iNode[useINode].filelen = filelen;    //文件长度
	(*fileSystem).iNode[useINode].qcount = 1;     //文件的引用数
	iNode[useINode] = 0;
	if (type == 1){                                   //1表示目录
		int useSFD = (*fileSystem).superBlock.freeSFD[0];
		vector<int>::iterator iter = (*fileSystem).superBlock.freeSFD.begin();
		iter = (*fileSystem).superBlock.freeSFD.erase(iter);  //从超级块freeSFD 中擦除
		(*fileSystem).iNode[useINode].sfd_id = useSFD;
		SFDBlock[useSFD] = 0; //位视图占用
		(*fileSystem).superBlock.free_SFD--;
		(*fileSystem).sfd[useSFD].sfdNum = 0;
	}
	else{
		(*fileSystem).iNode[useINode].sfd_id = -1;   //i结点sfd_id=-1表示结点中存放的是文件内容
	}
}

//创建一个目录
int createDir(string filename, FileSystem* fileSystem, string user, int* iNode, int* SFDBlock, int cur_SFD){
	//创建一个目录
	SingleSFD tempSFD;
	if ((*fileSystem).superBlock.freei_node == 0 || (*fileSystem).superBlock.free_SFD == 0){ //判断是否有空闲总结点和空闲目录
		setFontColor(12);
		cout << "i结点或目录空间不足，创建目录失败！\n";
		return 0;
	}

	//初始化目录
	tempSFD.name = filename;
	tempSFD.delink = 1;//初始成被链接文件
	int useINode = (*fileSystem).superBlock.freeiid[0];   //空闲i结点id数组第一个位置
	vector<int>::iterator iter = (*fileSystem).superBlock.freeiid.begin();      //分配空闲i结点
	iter = (*fileSystem).superBlock.freeiid.erase(iter);   //从超级块中擦除
	(*fileSystem).superBlock.freei_node--;     //空闲i结点总数-1
	iNode[useINode] = 0;          //修改位示图为占用状态
	tempSFD.id = useINode;        //修改sfd对应的i结点
	(*fileSystem).sfd[cur_SFD].sfdVec.push_back(tempSFD);    //目录下的sfd数组插入（vector）
	(*fileSystem).sfd[cur_SFD].sfdNum++;    //动态数组的大小+1
	//同步i结点信息
	createInitINode(useINode, 1, 0, fileSystem, user, iNode, SFDBlock);    //这里创建的文件长度为0
	return 1;
}

//级联删除一个目录及其子目录和子文件
int deleteDir(string name, FileSystem* fileSystem, int cur_SFD, int* iNode, int* SFDBlock, int* diskBlock, string user){
	//级联删除指定名字的目录及其子目录子文件
	int pos = -1;
	vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin(); //当前目录下目录项指针
	for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){   //找到目录位置
		if ((*fileSystem).sfd[cur_SFD].sfdVec[i].name == name){
			pos = i;
			break;
		}
		iter++;
	}
	if (pos == -1){
		setFontColor(12);
		cout << "删除失败，不存在的目录名！\n";
		return 0;
	}

	int useINode = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id; //useINODe 为将要删除目录所对应的i结点进行级联删除
	deleteINodeOne(useINode, cur_SFD, fileSystem, iNode, SFDBlock, diskBlock, user);  //删除i结点
	(*fileSystem).superBlock.freeiid.push_back(useINode);  //把释放的i结点放入到空闲块
	iNode[useINode] = 1;   //修改位示图
	(*fileSystem).superBlock.freei_node++;  //空闲i结点总数+1
	iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);  //当前目录指针擦除
	(*fileSystem).sfd[cur_SFD].sfdNum--; //当前目录下目录项减一
}


//删除一个i结点
void deleteINodeOne(int useINode, int cur_SFD, FileSystem* fileSystem, int* iNode, int* SFDBlock, int* diskBlock, string user){
	//级联删除i结点及其下级目录
	int preSFD = cur_SFD;                              //当前目录
	int useSFD = (*fileSystem).iNode[useINode].sfd_id;     //i结点对应的目录id，对应文件时为-1
	cur_SFD = useSFD;                                   //下一级目录
	while ((*fileSystem).sfd[cur_SFD].sfdVec.size() != 0){
		int nextInode = (*fileSystem).sfd[cur_SFD].sfdVec[0].id;
		if ((*fileSystem).iNode[nextInode].type == 0)
			freeFile((*fileSystem).sfd[cur_SFD].sfdVec[0].name, fileSystem, cur_SFD, user, iNode, diskBlock, SFDBlock);   //类型表示，0表示文件
		else
			deleteDir((*fileSystem).sfd[cur_SFD].sfdVec[0].name, fileSystem, cur_SFD, iNode, SFDBlock, diskBlock, user);  //1表示目录
	}
	(*fileSystem).sfd[cur_SFD].sfdVec.clear();
	(*fileSystem).sfd[cur_SFD].sfdNum = 0;      //数组大小
	(*fileSystem).superBlock.free_SFD++;
	(*fileSystem).superBlock.freeSFD.push_back(cur_SFD);
	SFDBlock[cur_SFD] = 1;
	cur_SFD = preSFD;       //返回上一级目录中
}
