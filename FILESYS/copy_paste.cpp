#include "FILE.h"

//����ָ�����ֵ�Ŀ¼���ļ�ʵ���ļ�����
int copyContext(string filename, FileSystem fileSystem, int cur_SFD, SingleSFD* copySFD, int* copy_flag){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
		if (fileSystem.sfd[cur_SFD].sfdVec[i].name == filename){   //�ҵ��ļ�����λ��
			pos = i;
			break;
		}
	}
	if (pos == -1){
		setFontColor(12);
		cout << "����ʧ�ܣ������ڵ��ļ���\n";
		return 0;
	}
	(*copySFD).name = fileSystem.sfd[cur_SFD].sfdVec[pos].name;   //�������ļ����ļ���
	(*copySFD).id = fileSystem.sfd[cur_SFD].sfdVec[pos].id;       //�ļ���Ӧ��i����id��
	if (fileSystem.iNode[(*copySFD).id].type == 1 && *copy_flag == 3) {
		setFontColor(12);
		cout << "Ŀ¼��������" << endl;
		return 0;
	}
	else if (fileSystem.iNode[(*copySFD).id].type == 1 && *copy_flag == 1) {
		setFontColor(12);
		cout << "Ŀ¼���ɸ���" << endl;
		return 0;
	}
	if (*copy_flag == 3)   //�����ļ�
		(*copySFD).delink = 0;
	else if (*copy_flag == 1)   //�����ļ�
		(*copySFD).delink = fileSystem.sfd[cur_SFD].sfdVec[pos].delink;
	return 1;
}

int cutContext(string filename, SingleSFD* copySFD, FileSystem* fileSystem, int cur_SFD){
	int flag = -1;
	vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin(); //512��SFDblock
	for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){  //�ҵ��������ļ����ֵ�λ��
		if (iter->name == filename){
			flag = 1;
			break;
		}
		iter++;
	}
	if (flag == -1){
		setFontColor(12);
		cout << "����ʧ�ܣ������ڵ��ļ���\n";
		return 0;
	}
	else if (flag == 1){
		(*copySFD).name = iter->name;
		(*copySFD).id = iter->id;
		(*copySFD).delink = 1;    //����Ŀ¼�����óɱ�����ģʽ
		(*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);    //��Ŀ¼�ṹ�в�����ǰĿ¼��
		(*fileSystem).sfd[cur_SFD].sfdNum--;
		return 1;
	}
}

//paste��������ռ�Ĵ��̿��С
int blocksNeeded(FileSystem* fileSystem, int* iNode, int* diskBlock, SingleSFD copySFD) {
	int iNodeId = copySFD.id;				//i�ڵ���
	int indexBlockId = fileSystem->iNode[iNodeId].diskBlockId;			//�������
	int blocksNeeded = 0;
	int* iaddr = getIaddr(indexBlockId, *fileSystem);			//һ����������
	int endFlag = 0;						//ֹͣ����
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
				int *iaddr2 = getIaddr(iaddr[i], *fileSystem);   //��������
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



//ճ��ճ�����ϵ����ݵ���ǰĿ¼��
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
			cout << "ʧ�ܣ���ǰĿ¼���Ѿ�������ճ������ͬ�����ļ���Ŀ¼��\n";
			return 0;
		}
		if (copy_flag == 2 || copy_flag == 3){//���ӻ����
			int id = copySFD.id;
			if (copy_flag == 3)
				(*fileSystem).iNode[id].qcount++;
			(*fileSystem).sfd[cur_SFD].sfdNum++;//�޸�
			(*fileSystem).sfd[cur_SFD].sfdVec.push_back(copySFD);//ֻ����sfd��Ϣ
			setFontColor(10);
			return 1;
			//cout << "ճ���ɹ�\n";
		}
		else{//�������ڴ�Ŀ¼�´���һ�����ļ�
			if ((*fileSystem).superBlock.freeDisk < blocksNeeded(fileSystem, iNode, diskBlock, copySFD)) {
				setFontColor(12);
				cout << "���̿ռ䲻�㣬����ʧ�ܣ�" << endl;
				return 0;
			}
			int cur_inode = getInodeNum(iNode, *fileSystem, cur_SFD);
			if ((*fileSystem).iNode[cur_inode].id != checkUser(user)){
				setFontColor(12);
				cout << "����ʧ�ܣ���û���ڸ�Ŀ¼�´����ļ���Ȩ��" << endl;
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
					cout << "����ʧ�ܣ�" << endl;
					return 0;
				}
				int inodeNo = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;     //�ҵ��´����ļ���i�ڵ��
				int indexnum = (*fileSystem).iNode[inodeNo].diskBlockId;     //��ռ���̿��id�ŵ�������
				int *iaddr = getIaddr(indexnum, *fileSystem);   //�õ��������д�ŵ�����

				int copy_indexnum = (*fileSystem).iNode[copySFD.id].diskBlockId; //�����ļ���ռ���̿��id�ŵ�������
				int *copy_iaddr = getIaddr(copy_indexnum, *fileSystem);   //�õ��������д�ŵ�����

				//iaddr[0] = copy_iaddr[0];
				int endflag = 0;
				for (int i = 0; i < 10; ++i){
					if (copy_iaddr[i] != -1){
						iaddr[i] = allocateOneBlock(fileSystem, diskBlock);
						if (iaddr[i] < 0) {
							cout << "���̿�����������ʧ�ܣ�" << endl;
							return 0;
						}
						(*fileSystem).iNode[inodeNo].diskBlockNum++;
						(*fileSystem).diskBlock[iaddr[i]].file = (*fileSystem).diskBlock[copy_iaddr[i]].file;    //ճ���ļ�����
						(*fileSystem).diskBlock[iaddr[i]].strNum = (*fileSystem).diskBlock[copy_iaddr[i]].strNum;   //ճ���ļ�����
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
							int *copy_iaddr2 = getIaddr(iaddr[i], *fileSystem);			//ԭ�ļ�������������
							int iaddr2[128];											//���ļ�������������
							for (int k = 0; k < 128; k++) {
								iaddr2[k] = -1;
							}
							for (int j = 0; j < 128; j++) {
								if (copy_iaddr2[j] == -1) {
									endflag = 1;
									break;
								}
								else {
									iaddr2[j] = allocateOneBlock(fileSystem, diskBlock);   //������������ճ��
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
		cout << "ճ����Ϊ��\n";
		return 0;
	}
}