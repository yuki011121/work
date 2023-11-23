#include "FILE.h"

int* getIaddr(int indexnum, FileSystem fileSystem) {//�õ��������д�ŵ�����

	string str[256];
	for (int i = 0; i < 256; i++)
		str[i] = "";
	int* iaddr = new int[256];
	int flag = 0;
	for (int j = 0, i = 0; j < fileSystem.diskBlock[indexnum].file.size(); j++) {//����������������У�
		if (fileSystem.diskBlock[indexnum].file[j] == ' ' && flag == 0) {
			continue;
		}
		else if (fileSystem.diskBlock[indexnum].file[j] == ' ') {
			i++;
			flag = 0;
		}
		else {
			flag = 1;
			str[i] += fileSystem.diskBlock[indexnum].file[j];//���������ڵ����ݷŽ�str����
		}
	}

	int i = 0;
	while (str[i] != "") {
		iaddr[i] = atoi(str[i].c_str());//�⺯�������ַ�ת������
		i++;
	}
	return iaddr;
}


//���ص�ǰ�ļ���ռ�õ������̿�
int getCur_blockNo(int inodeNo, FileSystem fileSystem) {
	int blocknum = fileSystem.iNode[inodeNo].diskBlockNum;  //�ļ�ռ�ô��̿����
	int indexnum = fileSystem.iNode[inodeNo].diskBlockId;   //��ռ���̿��id�ŵ�������
	if (blocknum == 1) {
		return -2;
	}
	else if (blocknum > 1) {
		int* iaddr = getIaddr(indexnum, fileSystem);   //�õ��������д�ŵ�����
		for (int i = 0; i < 10; i++) {
			if (iaddr[i] == -1)
				return iaddr[i - 1];    //���һ����-1����
		}
		for (int j = 10; j < 13; j++) {
			if (iaddr[j] == -1) {
				if (j == 10)
					return iaddr[j - 1];
				else {
					int* iaddr_f1 = getIaddr(iaddr[j - 1], fileSystem);
					return iaddr_f1[127];           //0-9��ֱ�ӣ�10-12���
				}
			}
			else {
				int* iaddr_1 = getIaddr(iaddr[j], fileSystem);//��������
				for (int i = 0; i < 128; i++) {//�����ڶ�������
					if (iaddr_1[i] == -1)
						return iaddr_1[i - 1];
				}
			}
		}
	}
	return -1;
}


//�������е���������д�ص���Ӧ���������У������ļ���
void writeiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem) { //д������ļ��У����ļ���д�ļ�,Block�Ƕ�Ӧ��������Ŀ��
	(*fileSystem).diskBlock[BlockNo].file = "";
	for (int i = 0; i < 13; i++) {
		string str;
		stringstream ss;
		ss << iaddr[i];
		ss >> str;
		(*fileSystem).diskBlock[BlockNo].file = (*fileSystem).diskBlock[BlockNo].file + str + " ";
	}
	(*fileSystem).diskBlock[BlockNo].strNum = (*fileSystem).diskBlock[BlockNo].file.size();//���³���
}


void secondWriteiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem) {
	(*fileSystem).diskBlock[BlockNo].file = "";//д�ڶ�������
	for (int i = 0; i < 128; i++) {
		string str;
		stringstream ss;
		ss << iaddr[i];
		ss >> str;//����ֵת�����ַ���������
		(*fileSystem).diskBlock[BlockNo].file = (*fileSystem).diskBlock[BlockNo].file + " " + str;
	}
	(*fileSystem).diskBlock[BlockNo].strNum = (*fileSystem).diskBlock[BlockNo].file.size();//���³���
}

int writeIndexBlock(int indexnum, int BlockNo, FileSystem* fileSystem, int* diskBlock) {

	int* iaddr = getIaddr(indexnum, *fileSystem);         //��������������
	for (int i = 0; i < 10; i++) {//ֱ������
		if (iaddr[i] == -1) {

			iaddr[i] = BlockNo;
			writeiaddr(indexnum, iaddr, fileSystem);
			delete[] iaddr;
			return BlockNo;                 //�������д��Ŀ��
		}
	}

	for (int j = 10; j < 13; j++) {
		if (iaddr[j] == -1) {                          //˵����һ����μ�ַ���������ģ�ֻ�ܴӵ�ǰ���ٽ��µĶ�������
			iaddr[j] = BlockNo;                      //BlockNo��Ҫ����������еĿ��
			writeiaddr(indexnum, iaddr, fileSystem);
			int cur_B = allocateOneBlock(fileSystem, diskBlock);//������̿�
			if (cur_B == -1) {
				cout << "�޷������µ�������" << endl;
				return -1;
			}
			(*fileSystem).diskBlock[BlockNo].strNum = 128;
			int iaddr_all1[128];
			for (int i = 0; i < 128; i++) {//��ʼ��ȫΪ-1
				iaddr_all1[i] = -1;
			}
			iaddr_all1[0] = cur_B;                  //iaddre_all1[0]�д�ŵ��Ƕ�����������
			writeiaddr(BlockNo, iaddr_all1, fileSystem);
			secondWriteiaddr(BlockNo, iaddr_all1, fileSystem);
			delete[] iaddr;
			return cur_B;                           //�������д��Ŀ��
		}
		else {                                 //����ֱ���ڶ�������������Ӧ�Ŀ�λд�뵱ǰ���
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
	cout << "�������ļ�����..." << endl;
	readFile(name, *fileSystem, cur_SFD);
	writeContent(content);
	if (content.length() == 0)
		return 1;
	if (!writeDisk(pos, fileSystem, cur_SFD, diskBlock, content))
		cout << "д����ʧ��" << endl;
	return 0;
}


void writeContent(string& content) {
	//getchar();
	fflush(stdin);// ����fflush()�Ὣ�������е�����д��stream��ָ���ļ���ȥ
	char ch = getch(); //����ascii��
	while (ch != 27) {//esc��
		if (ch == 13) {//�س�
			setFontColor(15);
			printf("\n");
			content += '\n';
		}
		else if (ch == 8) {//�˸�back
			int size = content.size();
			if (size > 0) {
				if (content.at(size - 1) != '\n') {
					content.erase(content.size() - 1);//ɾ�����һ���ַ�
					fflush(stdout);
					putchar('\b');//ת���ַ��˸�
					fflush(stdout);
					putchar(' ');
					fflush(stdout);
					putchar('\b');
					fflush(stdout);
				}
				else {
					content.erase(content.size() - 1);
					fflush(stdout); //fflush �����þ���ֱ�Ӱѻ����������ݴ�ӡ����Ļ�ϣ�����ջ����������صȻ��з�
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
	printf("\n�����˳�y�������༭n��");
	ch = getchar();
	while (ch != 'y' || ch != 'Y' || ch != 'N' || ch != 'n') {
		if (ch == 'y' || ch == 'Y') {
			setFontColor(10);
			cout << "����ɹ�";
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

	int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;     //�ҵ������ļ���i����
	int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;     //��ռ���̿��id�ŵ�������
	int cur_blockNo = getCur_blockNo(inodeNo, *fileSystem);      //���ص�ǰ�ļ�����ռ�����һ����̿�

	if (cur_blockNo == -1) {
		setFontColor(12);
		cout << "д�ļ����ִ��̿�洢����\n";
		return 0;
	}
	else if (cur_blockNo == -2) {               //�ļ�����Ӧ�Ĵ��̿����Ϊ1������-2
		cur_blockNo = allocateOneBlock(fileSystem, diskBlock);//������̿�
		if (cur_blockNo < 0)
			return 0;
		(*fileSystem).iNode[inodeNo].diskBlockNum++;
		cur_blockNo = writeIndexBlock(indexnum, cur_blockNo, fileSystem, diskBlock);//δ����-1�����
	}

	while (content != "") {
		int size = DISK_LEN - (*fileSystem).diskBlock[cur_blockNo].strNum;//ʣ��ռ�
		if (size >= content.length()) {
			(*fileSystem).diskBlock[cur_blockNo].file += content;
			(*fileSystem).diskBlock[cur_blockNo].strNum += content.length();
			content = "";
		}
		else {
			(*fileSystem).diskBlock[cur_blockNo].file += content.substr(0, size);
			(*fileSystem).diskBlock[cur_blockNo].strNum = DISK_LEN;
			content.erase(0, size);//�����Ѿ�д����
			cur_blockNo = allocateOneBlock(fileSystem, diskBlock);//�����µ�
			if (cur_blockNo < 0)
				return 0;//����ʧ��
			int last_blockNo = cur_blockNo;
			(*fileSystem).iNode[inodeNo].diskBlockNum++;
			cur_blockNo = writeIndexBlock(indexnum, cur_blockNo, fileSystem, diskBlock);//�������̿�һ��13�飬-1����
			if (cur_blockNo == -1) {
				freeABlock(last_blockNo, diskBlock, fileSystem, NULL);//�����Ѿ�����Ĵ��̿�
				cout << "������ռ��" << endl;
				return 0;
			}
		}
	}
	return 1;
}

//����ļ����̿�����
void outputBlock(int blockNO, FileSystem fileSystem) {
	string output;
	output = fileSystem.diskBlock[blockNO].file;
	setFontColor(15);
	cout << output;
}

//���ļ����ݺ���
void readFile(string name, FileSystem fileSystem, int cur_SFD) {

	int pos = checkExitsfd(name, fileSystem, cur_SFD);  //�鿴�ǵ�ǰĿ¼�µĵڼ����ļ�
	if (pos == -1) {
		setFontColor(12);
		cout << "�ļ�������\n";
	}
	else {
		int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;   //�ļ���Ӧ��i�����
		int indexnum = fileSystem.iNode[inodeNo].diskBlockId;    //�ļ���Ӧ��������
		int* iaddr = getIaddr(indexnum, fileSystem);                      //��Ӧ���̿��е�����
		for (int i = 0; i < 10; i++) {
			if (iaddr[i] != -1)
				outputBlock(iaddr[i], fileSystem);  //iaddr[i]��ֱ�Ӵ���ļ����ݣ���ֱ�����
			else {
				//cout << endl; //�ļ��������
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