#include "FILE.h"

//Ϊ�����ļ���Ŀ¼��ʼ��i���
void createInitINode(int useINode, int type, int filelen, FileSystem* fileSystem, string user, int* iNode, int* SFDBlock){

	//�½�Ŀ¼���ļ�ʱ��ʼ��i���
	(*fileSystem).iNode[useINode].id = checkUser(user);  //i��������û�
	(*fileSystem).iNode[useINode].type = type;     //�ļ�����
	(*fileSystem).iNode[useINode].filelen = filelen;    //�ļ�����
	(*fileSystem).iNode[useINode].qcount = 1;     //�ļ���������
	iNode[useINode] = 0;
	if (type == 1){                                   //1��ʾĿ¼
		int useSFD = (*fileSystem).superBlock.freeSFD[0];
		vector<int>::iterator iter = (*fileSystem).superBlock.freeSFD.begin();
		iter = (*fileSystem).superBlock.freeSFD.erase(iter);  //�ӳ�����freeSFD �в���
		(*fileSystem).iNode[useINode].sfd_id = useSFD;
		SFDBlock[useSFD] = 0; //λ��ͼռ��
		(*fileSystem).superBlock.free_SFD--;
		(*fileSystem).sfd[useSFD].sfdNum = 0;
	}
	else{
		(*fileSystem).iNode[useINode].sfd_id = -1;   //i���sfd_id=-1��ʾ����д�ŵ����ļ�����
	}
}

//����һ��Ŀ¼
int createDir(string filename, FileSystem* fileSystem, string user, int* iNode, int* SFDBlock, int cur_SFD){
	//����һ��Ŀ¼
	SingleSFD tempSFD;
	if ((*fileSystem).superBlock.freei_node == 0 || (*fileSystem).superBlock.free_SFD == 0){ //�ж��Ƿ��п����ܽ��Ϳ���Ŀ¼
		setFontColor(12);
		cout << "i����Ŀ¼�ռ䲻�㣬����Ŀ¼ʧ�ܣ�\n";
		return 0;
	}

	//��ʼ��Ŀ¼
	tempSFD.name = filename;
	tempSFD.delink = 1;//��ʼ�ɱ������ļ�
	int useINode = (*fileSystem).superBlock.freeiid[0];   //����i���id�����һ��λ��
	vector<int>::iterator iter = (*fileSystem).superBlock.freeiid.begin();      //�������i���
	iter = (*fileSystem).superBlock.freeiid.erase(iter);   //�ӳ������в���
	(*fileSystem).superBlock.freei_node--;     //����i�������-1
	iNode[useINode] = 0;          //�޸�λʾͼΪռ��״̬
	tempSFD.id = useINode;        //�޸�sfd��Ӧ��i���
	(*fileSystem).sfd[cur_SFD].sfdVec.push_back(tempSFD);    //Ŀ¼�µ�sfd������루vector��
	(*fileSystem).sfd[cur_SFD].sfdNum++;    //��̬����Ĵ�С+1
	//ͬ��i�����Ϣ
	createInitINode(useINode, 1, 0, fileSystem, user, iNode, SFDBlock);    //���ﴴ�����ļ�����Ϊ0
	return 1;
}

//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
int deleteDir(string name, FileSystem* fileSystem, int cur_SFD, int* iNode, int* SFDBlock, int* diskBlock, string user){
	//����ɾ��ָ�����ֵ�Ŀ¼������Ŀ¼���ļ�
	int pos = -1;
	vector<SingleSFD>::iterator iter = (*fileSystem).sfd[cur_SFD].sfdVec.begin(); //��ǰĿ¼��Ŀ¼��ָ��
	for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){   //�ҵ�Ŀ¼λ��
		if ((*fileSystem).sfd[cur_SFD].sfdVec[i].name == name){
			pos = i;
			break;
		}
		iter++;
	}
	if (pos == -1){
		setFontColor(12);
		cout << "ɾ��ʧ�ܣ������ڵ�Ŀ¼����\n";
		return 0;
	}

	int useINode = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id; //useINODe Ϊ��Ҫɾ��Ŀ¼����Ӧ��i�����м���ɾ��
	deleteINodeOne(useINode, cur_SFD, fileSystem, iNode, SFDBlock, diskBlock, user);  //ɾ��i���
	(*fileSystem).superBlock.freeiid.push_back(useINode);  //���ͷŵ�i�����뵽���п�
	iNode[useINode] = 1;   //�޸�λʾͼ
	(*fileSystem).superBlock.freei_node++;  //����i�������+1
	iter = (*fileSystem).sfd[cur_SFD].sfdVec.erase(iter);  //��ǰĿ¼ָ�����
	(*fileSystem).sfd[cur_SFD].sfdNum--; //��ǰĿ¼��Ŀ¼���һ
}


//ɾ��һ��i���
void deleteINodeOne(int useINode, int cur_SFD, FileSystem* fileSystem, int* iNode, int* SFDBlock, int* diskBlock, string user){
	//����ɾ��i��㼰���¼�Ŀ¼
	int preSFD = cur_SFD;                              //��ǰĿ¼
	int useSFD = (*fileSystem).iNode[useINode].sfd_id;     //i����Ӧ��Ŀ¼id����Ӧ�ļ�ʱΪ-1
	cur_SFD = useSFD;                                   //��һ��Ŀ¼
	while ((*fileSystem).sfd[cur_SFD].sfdVec.size() != 0){
		int nextInode = (*fileSystem).sfd[cur_SFD].sfdVec[0].id;
		if ((*fileSystem).iNode[nextInode].type == 0)
			freeFile((*fileSystem).sfd[cur_SFD].sfdVec[0].name, fileSystem, cur_SFD, user, iNode, diskBlock, SFDBlock);   //���ͱ�ʾ��0��ʾ�ļ�
		else
			deleteDir((*fileSystem).sfd[cur_SFD].sfdVec[0].name, fileSystem, cur_SFD, iNode, SFDBlock, diskBlock, user);  //1��ʾĿ¼
	}
	(*fileSystem).sfd[cur_SFD].sfdVec.clear();
	(*fileSystem).sfd[cur_SFD].sfdNum = 0;      //�����С
	(*fileSystem).superBlock.free_SFD++;
	(*fileSystem).superBlock.freeSFD.push_back(cur_SFD);
	SFDBlock[cur_SFD] = 1;
	cur_SFD = preSFD;       //������һ��Ŀ¼��
}
