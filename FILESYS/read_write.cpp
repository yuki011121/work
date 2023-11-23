#include "FILE.h"

int* getIaddr(int indexnum, FileSystem fileSystem) {//得到索引块中存放的内容

	string str[256];
	for (int i = 0; i < 256; i++)
		str[i] = "";
	int* iaddr = new int[256];
	int flag = 0;
	for (int j = 0, i = 0; j < fileSystem.diskBlock[indexnum].file.size(); j++) {//遍历索引块的所有行？
		if (fileSystem.diskBlock[indexnum].file[j] == ' ' && flag == 0) {
			continue;
		}
		else if (fileSystem.diskBlock[indexnum].file[j] == ' ') {
			i++;
			flag = 0;
		}
		else {
			flag = 1;
			str[i] += fileSystem.diskBlock[indexnum].file[j];//把索引块内的内容放进str里面
		}
	}

	int i = 0;
	while (str[i] != "") {
		iaddr[i] = atoi(str[i].c_str());//库函数，将字符转成数字
		i++;
	}
	return iaddr;
}


//返回当前文件所占用的最后磁盘块
int getCur_blockNo(int inodeNo, FileSystem fileSystem) {
	int blocknum = fileSystem.iNode[inodeNo].diskBlockNum;  //文件占用磁盘块个数
	int indexnum = fileSystem.iNode[inodeNo].diskBlockId;   //所占磁盘块的id号的索引块
	if (blocknum == 1) {
		return -2;
	}
	else if (blocknum > 1) {
		int* iaddr = getIaddr(indexnum, fileSystem);   //得到索引块中存放的内容
		for (int i = 0; i < 10; i++) {
			if (iaddr[i] == -1)
				return iaddr[i - 1];    //最后一块以-1结束
		}
		for (int j = 10; j < 13; j++) {
			if (iaddr[j] == -1) {
				if (j == 10)
					return iaddr[j - 1];
				else {
					int* iaddr_f1 = getIaddr(iaddr[j - 1], fileSystem);
					return iaddr_f1[127];           //0-9是直接，10-12间接
				}
			}
			else {
				int* iaddr_1 = getIaddr(iaddr[j], fileSystem);//两级索引
				for (int i = 0; i < 128; i++) {//遍历第二级索引
					if (iaddr_1[i] == -1)
						return iaddr_1[i - 1];
				}
			}
		}
	}
	return -1;
}


//将数组中的索引内容写回到相应的索引块中，磁盘文件中
void writeiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem) { //写入磁盘文件中，读文件，写文件,Block是对应的索引块的块号
	(*fileSystem).diskBlock[BlockNo].file = "";
	for (int i = 0; i < 13; i++) {
		string str;
		stringstream ss;
		ss << iaddr[i];
		ss >> str;
		(*fileSystem).diskBlock[BlockNo].file = (*fileSystem).diskBlock[BlockNo].file + str + " ";
	}
	(*fileSystem).diskBlock[BlockNo].strNum = (*fileSystem).diskBlock[BlockNo].file.size();//更新长度
}


void secondWriteiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem) {
	(*fileSystem).diskBlock[BlockNo].file = "";//写第二级索引
	for (int i = 0; i < 128; i++) {
		string str;
		stringstream ss;
		ss << iaddr[i];
		ss >> str;//整数值转换成字符串存起来
		(*fileSystem).diskBlock[BlockNo].file = (*fileSystem).diskBlock[BlockNo].file + " " + str;
	}
	(*fileSystem).diskBlock[BlockNo].strNum = (*fileSystem).diskBlock[BlockNo].file.size();//更新长度
}

int writeIndexBlock(int indexnum, int BlockNo, FileSystem* fileSystem, int* diskBlock) {

	int* iaddr = getIaddr(indexnum, *fileSystem);         //读出索引块内容
	for (int i = 0; i < 10; i++) {//直接索引
		if (iaddr[i] == -1) {

			iaddr[i] = BlockNo;
			writeiaddr(indexnum, iaddr, fileSystem);
			delete[] iaddr;
			return BlockNo;                 //返回最后写入的块号
		}
	}

	for (int j = 10; j < 13; j++) {
		if (iaddr[j] == -1) {                          //说明上一块二次间址索引是满的，只能从当前的再建新的二级索引
			iaddr[j] = BlockNo;                      //BlockNo是要放入的索引中的块号
			writeiaddr(indexnum, iaddr, fileSystem);
			int cur_B = allocateOneBlock(fileSystem, diskBlock);//分配磁盘块
			if (cur_B == -1) {
				cout << "无法分配新的索引块" << endl;
				return -1;
			}
			(*fileSystem).diskBlock[BlockNo].strNum = 128;
			int iaddr_all1[128];
			for (int i = 0; i < 128; i++) {//初始化全为-1
				iaddr_all1[i] = -1;
			}
			iaddr_all1[0] = cur_B;                  //iaddre_all1[0]中存放的是二级索引块块号
			writeiaddr(BlockNo, iaddr_all1, fileSystem);
			secondWriteiaddr(BlockNo, iaddr_all1, fileSystem);
			delete[] iaddr;
			return cur_B;                           //返回最后写入的块号
		}
		else {                                 //否则直接在二级索引中找相应的空位写入当前块号
			int* iaddr_1 = getIaddr(iaddr[j], *fileSystem);
			for (int i = 0; i < 128; i++) {
				if (iaddr_1[i] == -1) {
					iaddr_1[i] = BlockNo;
					secondWriteiaddr(iaddr[j], iaddr_1, fileSystem);
					return BlockNo;
				}
			}
			delete iaddr_1;
		}
	}
	delete[] iaddr;
	return -1;
}

int writeFile(string name, FileSystem* fileSystem, int cur_SFD, int* diskBlock) {
	int pos = checkExitsfd(name, *fileSystem, cur_SFD);
	string content = "";
	int a;
	char filename[100];
	//char s[DISK_LEN * 394 + 2];
	setFontColor(10);
	cout << "请输入文件内容..." << endl;
	readFile(name, *fileSystem, cur_SFD);
	writeContent(content);
	if (content.length() == 0)
		return 1;
	if (!writeDisk(pos, fileSystem, cur_SFD, diskBlock, content))
		cout << "写磁盘失败" << endl;
	return 0;
}


void writeContent(string& content) {
	//getchar();
	fflush(stdin);// 调用fflush()会将缓冲区中的内容写到stream所指的文件中去
	char ch = getch(); //返回ascii码
	while (ch != 27) {//esc键
		if (ch == 13) {//回车
			setFontColor(15);
			printf("\n");
			content += '\n';
		}
		else if (ch == 8) {//退格back
			int size = content.size();
			if (size > 0) {
				if (content.at(size - 1) != '\n') {
					content.erase(content.size() - 1);//删除最后一个字符
					fflush(stdout);
					putchar('\b');//转义字符退格
					fflush(stdout);
					putchar(' ');
					fflush(stdout);
					putchar('\b');
					fflush(stdout);
				}
				else {
					content.erase(content.size() - 1);
					fflush(stdout); //fflush 的作用就是直接把缓冲区的内容打印到屏幕上，并清空缓冲区。不必等换行符
					putchar('\b');
					putchar('\r');
					fflush(stdout);
					int pos = content.rfind('\n');
					if (pos == std::string::npos)
						cout << content;
					else {
						string str = content.substr(pos + 1);
						cout << str;
					}
				}
			}
		}
		else {
			setFontColor(15);
			putchar(ch);
			content += ch;
		}

		ch = getch();
	}
	printf("\n保存退出y，放弃编辑n：");
	ch = getchar();
	while (ch != 'y' || ch != 'Y' || ch != 'N' || ch != 'n') {
		if (ch == 'y' || ch == 'Y') {
			setFontColor(10);
			cout << "保存成功";
			return;
		}
		else if (ch == 'N' || ch == 'n') {
			content = "";
			return;
		}
		ch = getchar();
	}
}

int writeDisk(int pos, FileSystem* fileSystem, int cur_SFD, int* diskBlock, string content) {

	int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;     //找到已有文件的i结点号
	int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;     //所占磁盘块的id号的索引块
	int cur_blockNo = getCur_blockNo(inodeNo, *fileSystem);      //返回当前文件所对占的最后一块磁盘块

	if (cur_blockNo == -1) {
		setFontColor(12);
		cout << "写文件发现磁盘块存储错误\n";
		return 0;
	}
	else if (cur_blockNo == -2) {               //文件所对应的磁盘块个数为1，返回-2
		cur_blockNo = allocateOneBlock(fileSystem, diskBlock);//分配磁盘块
		if (cur_blockNo < 0)
			return 0;
		(*fileSystem).iNode[inodeNo].diskBlockNum++;
		cur_blockNo = writeIndexBlock(indexnum, cur_blockNo, fileSystem, diskBlock);//未考虑-1的情况
	}

	while (content != "") {
		int size = DISK_LEN - (*fileSystem).diskBlock[cur_blockNo].strNum;//剩余空间
		if (size >= content.length()) {
			(*fileSystem).diskBlock[cur_blockNo].file += content;
			(*fileSystem).diskBlock[cur_blockNo].strNum += content.length();
			content = "";
		}
		else {
			(*fileSystem).diskBlock[cur_blockNo].file += content.substr(0, size);
			(*fileSystem).diskBlock[cur_blockNo].strNum = DISK_LEN;
			content.erase(0, size);//擦除已经写过的
			cur_blockNo = allocateOneBlock(fileSystem, diskBlock);//分配新的
			if (cur_blockNo < 0)
				return 0;//分配失败
			int last_blockNo = cur_blockNo;
			(*fileSystem).iNode[inodeNo].diskBlockNum++;
			cur_blockNo = writeIndexBlock(indexnum, cur_blockNo, fileSystem, diskBlock);//索引磁盘块一共13块，-1满了
			if (cur_blockNo == -1) {
				freeABlock(last_blockNo, diskBlock, fileSystem, NULL);//回收已经分配的磁盘块
				cout << "索引块占满" << endl;
				return 0;
			}
		}
	}
	return 1;
}

//输出文件磁盘块内容
void outputBlock(int blockNO, FileSystem fileSystem) {
	string output;
	output = fileSystem.diskBlock[blockNO].file;
	setFontColor(15);
	cout << output;
}

//读文件内容函数
void readFile(string name, FileSystem fileSystem, int cur_SFD) {

	int pos = checkExitsfd(name, fileSystem, cur_SFD);  //查看是当前目录下的第几个文件
	if (pos == -1) {
		setFontColor(12);
		cout << "文件不存在\n";
	}
	else {
		int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;   //文件对应的i结点编号
		int indexnum = fileSystem.iNode[inodeNo].diskBlockId;    //文件对应的索引块
		int* iaddr = getIaddr(indexnum, fileSystem);                      //对应磁盘块中的内容
		for (int i = 0; i < 10; i++) {
			if (iaddr[i] != -1)
				outputBlock(iaddr[i], fileSystem);  //iaddr[i]中直接存放文件内容，可直接输出
			else {
				//cout << endl; //文件输出结束
				return;
			}
		}

		for (int j = 10; j < 13; j++) {
			if (iaddr[j] == -1)
				return;
			else {
				int* iaddr_1 = getIaddr(iaddr[j], fileSystem);
				for (int i = 0; i < 128; i++) {
					if (iaddr_1[i] != -1)
						outputBlock(iaddr_1[i], fileSystem);
					else
						return;
				}
				delete iaddr_1;
			}
		}
		delete[] iaddr;
	}
}