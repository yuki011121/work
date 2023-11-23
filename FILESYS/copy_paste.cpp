#include "FILE.h"

//复制指定名字的目录或文件实现文件共享
int copyContext(string filename, FileSystem fileSystem, int cur_SFD, SingleSFD* copySFD, int* copy_flag){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
		if (fileSystem.sfd[cur_SFD].sfdVec[i].name == filename){   //找到文件名的位置
			pos = i;
			break;
		}
	}
	if (pos == -1){
		setFontColor(12);
		cout << "复制失败，不存在的文件名\n";
		return 0;
	}
	(*copySFD).name = fileSystem.sfd[cur_SFD].sfdVec[pos].name;   //被复制文件的文件名
	(*copySFD).id = fileSystem.sfd[cur_SFD].sfdVec[pos].id;       //文件对应的i结点的id号
	if (fileSystem.iNode[(*copySFD).id].type == 1 && *copy_flag == 3) {
		setFontColor(12);
		cout << "目录不可链接" << endl;
		return 0;
	}
	else if (fileSystem.iNode[(*copySFD).id].type == 1 && *copy_flag == 1) {
		setFontColor(12);
		cout << "目录不可复制" << endl;
		return 0;
	}
	if (*copy_flag == 3)   //链接文件
		(*copySFD).delink = 0;
	else if (*copy_flag == 1)   //复制文件
		(*copySFD).delink = fileSystem.sfd[cur_SFD].sfdVec[pos].delink;
	return 1;
}

int cutContext(string filename, SingleSFD* copySFD, FileSystem* fileSystem, int cur_SFD){
	int flag = -1;
	vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin(); //512个SFDblock
	for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){  //找到被剪切文件名字的位置
		if (iter->name == filename){
			flag = 1;
			break;
		}
		iter++;
	}
	if (flag == -1){
		setFontColor(12);
		cout << "剪切失败，不存在的文件名\n";
		return 0;
	}
	else if (flag == 1){
		(*copySFD).name = iter->name;
		(*copySFD).id = iter->id;
		(*copySFD).delink = 1;    //单个目录项设置成被链接模式
		(*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //在目录结构中擦除当前目录项
		(*fileSystem).sfd[cur_SFD].sfdNum--;
		return 1;
	}
}

//paste的内容所占的磁盘块大小
int blocksNeeded(FileSystem* fileSystem, int* iNode, int* diskBlock, SingleSFD copySFD) {
	int iNodeId = copySFD.id;				//i节点编号
	int indexBlockId = fileSystem->iNode[iNodeId].diskBlockId;			//索引块号
	int blocksNeeded = 0;
	int* iaddr = getIaddr(indexBlockId, *fileSystem);			//一级索引数组
	int endFlag = 0;						//停止查找
	for (int i = 0; i < 10; i++) {
		if (iaddr[i] == -1) {
			endFlag = 1;
			break;
		}
		else {
			blocksNeeded++;
		}
	}
	if (endFlag == 0) {
		for (int i = 10; i < 13; i++) {
			if (iaddr[i] == -1 || endFlag == 1) {
				endFlag = 1;
				break;
			}
			else {
				blocksNeeded++;
				int *iaddr2 = getIaddr(iaddr[i], *fileSystem);   //二级索引
				for (int j = 0; j < 128; j++) {
					if (iaddr2[j] == -1) {
						endFlag = 1;
						break;
					}
					else {
						blocksNeeded++;
					}
				}
				delete[] iaddr2;
			}
		}
	}
	delete[] iaddr;
	return blocksNeeded;
}



//粘贴粘贴板上的内容到当前目录下
int pasteContext(int copy_flag, SingleSFD copySFD, int cur_SFD,
	FileSystem* fileSystem, string user, int* iNode, int* diskBlock, int* SFDBlock)
{
	if (copy_flag > 0){
		int pos = -1;
		for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){
			if (copySFD.name == (*fileSystem).sfd[cur_SFD].sfdVec[i].name){
				pos = i;
				break;
			}
		}
		if (pos != -1){
			setFontColor(12);
			cout << "失败，当前目录下已经存在与粘贴板上同名的文件或目录！\n";
			return 0;
		}
		if (copy_flag == 2 || copy_flag == 3){//链接或剪切
			int id = copySFD.id;
			if (copy_flag == 3)
				(*fileSystem).iNode[id].qcount++;
			(*fileSystem).sfd[cur_SFD].sfdNum++;//修改
			(*fileSystem).sfd[cur_SFD].sfdVec.push_back(copySFD);//只保存sfd信息
			setFontColor(10);
			return 1;
			//cout << "粘贴成功\n";
		}
		else{//拷贝，在此目录下创建一个新文件
			if ((*fileSystem).superBlock.freeDisk < blocksNeeded(fileSystem, iNode, diskBlock, copySFD)) {
				setFontColor(12);
				cout << "磁盘空间不足，拷贝失败！" << endl;
				return 0;
			}
			int cur_inode = getInodeNum(iNode, *fileSystem, cur_SFD);
			if ((*fileSystem).iNode[cur_inode].id != checkUser(user)){
				setFontColor(12);
				cout << "创建失败，您没有在该目录下创建文件的权限" << endl;
				return 0;
			}
			if (createFile(copySFD.name, fileSystem, cur_SFD, iNode, user, diskBlock, SFDBlock)){
				for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){
					if (copySFD.name == (*fileSystem).sfd[cur_SFD].sfdVec[i].name){
						pos = i;
						break;
					}
				}
				if (pos < 0){
					setFontColor(12);
					cout << "拷贝失败！" << endl;
					return 0;
				}
				int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;     //找到新创建文件的i节点号
				int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;     //所占磁盘块的id号的索引块
				int *iaddr = getIaddr(indexnum, *fileSystem);   //得到索引块中存放的内容

				int copy_indexnum = (*fileSystem).iNode[copySFD.id].diskBlockId; //复制文件所占磁盘块的id号的索引块
				int *copy_iaddr = getIaddr(copy_indexnum, *fileSystem);   //得到索引块中存放的内容

				//iaddr[0] = copy_iaddr[0];
				int endflag = 0;
				for (int i = 0; i < 10; ++i){
					if (copy_iaddr[i] != -1){
						iaddr[i] = allocateOneBlock(fileSystem, diskBlock);
						if (iaddr[i] < 0) {
							cout << "磁盘块已满，拷贝失败！" << endl;
							return 0;
						}
						(*fileSystem).iNode[inodeNo].diskBlockNum++;
						(*fileSystem).diskBlock[iaddr[i]].file = (*fileSystem).diskBlock[copy_iaddr[i]].file;    //粘贴文件内容
						(*fileSystem).diskBlock[iaddr[i]].strNum = (*fileSystem).diskBlock[copy_iaddr[i]].strNum;   //粘贴文件长度
					}
					else {
						endflag = 1;
						break;
					}
				}
				if (endflag == 0) {
					for (int i = 10; i < 13; i++) {
						if (copy_iaddr[i] == -1 || endflag == 1) {
							break;
						}
						else {
							iaddr[i] = allocateOneBlock(fileSystem, diskBlock);
							(*fileSystem).iNode[inodeNo].diskBlockNum++;
							(*fileSystem).diskBlock[iaddr[i]].file = (*fileSystem).diskBlock[copy_iaddr[i]].file;
							(*fileSystem).diskBlock[iaddr[i]].strNum = (*fileSystem).diskBlock[copy_iaddr[i]].strNum;
							int *copy_iaddr2 = getIaddr(iaddr[i], *fileSystem);			//原文件二级索引数组
							int iaddr2[128];											//新文件二级索引数组
							for (int k = 0; k < 128; k++) {
								iaddr2[k] = -1;
							}
							for (int j = 0; j < 128; j++) {
								if (copy_iaddr2[j] == -1) {
									endflag = 1;
									break;
								}
								else {
									iaddr2[j] = allocateOneBlock(fileSystem, diskBlock);   //二级索引内容粘贴
									(*fileSystem).iNode[inodeNo].diskBlockNum++;
									(*fileSystem).diskBlock[iaddr2[j]].file = (*fileSystem).diskBlock[copy_iaddr2[j]].file;
									(*fileSystem).diskBlock[iaddr2[j]].strNum = (*fileSystem).diskBlock[copy_iaddr2[j]].strNum;
								}
							}
							secondWriteiaddr(iaddr[i], iaddr2, fileSystem);
							delete[] copy_iaddr2;
						}
					}
				}
				writeiaddr(indexnum, iaddr, fileSystem);
				delete[] iaddr;
				delete[] copy_iaddr;
				return 1;

			}
		}
	}
	else{
		setFontColor(12);
		cout << "粘贴板为空\n";
		return 0;
	}
}