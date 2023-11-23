
#include "FILE.h"
string userName[8] = {"user1", "user2", "user3" ,"user4","user5", "user6", "user7", "user8"};
string pwd[8] = {"user1","user2","user3","user4","user5","user6","user7","user8"};
/**
 * @brief �û���¼
 *
 * @param user
 */
void login(User& user){
    MessageBox(nullptr, TEXT("��ӭʹ���ļ�ϵͳ��"), TEXT("WELCOME"), MB_OK); //��Ϣ����
    system("cls");
    setFontColor(11);
    cin.clear();//��� cin ����Ĵ���״̬��־��
    cin.sync(); //����������������� cin.ignore(std::numeric_limits<int>::max(),'\n');
    while (true){//����һ������ѭ����Ҫ���û������û�������������Ӧ�Ĵ���
        setFontColor(15);
        cout << "���¼�ļ�ϵͳ(����exit�˳��ļ�ϵͳ): ";
        cin >> user.userName;
        if (user.userName == "exit"){
            setFontColor(9);
            cout << "Bye~\n";
            Sleep(1000);
            exit(0);
        }
        int res = checkUser(user.userName);//����checkUser��������û��Ƿ���ڡ�
        if (!res){
            setFontColor(12);
            cout << "The user does not exist, please re-enter\n";
            continue;//����û������ڣ���ʾ������Ϣ��������Ҫ���û������û�����
        }else{
            setFontColor(15);
            string password="";
            cout << "����������: ";
            char c;
            while((c=getch())!=13) password+=c; //��ȡ�û��ļ������벢�ж��Ƿ���� ASCII ֵΪ 13 �Ļس�����
            if(password != pwd[res-1]){
                setFontColor(12);
                cout << "\nIncorrect password !!!\n";
                continue;
            }
        }
        for(int i = 0;i < NOFILE;i++){
            user.uOpenFile.SysOFId[i] = -1;//�� user ����� uOpenFile ��Ա�����е� SysOFId ���������Ԫ������Ϊ -1����ʾ�û��򿪵��ļ���ʶ����δ��ʹ��
        }
        setFontColor(10);
        cout << "\nSuccessful landing, Press enter to access the file system..." << endl;
        getchar();
        getchar();//��ȡ���λس������룬���ڵȴ��û����»س�������
        break;
    }

}

/**
 * @brief �жϵ�¼�û�
 *
 * @param user
 * @return int
 */
int checkUser(string user){
    if (user == "user1")
        return 1;
    else if (user == "user2")
        return 2;
    else if (user == "user3")
        return 3;
    else if (user == "user4")
        return 4;
    else if (user == "user5")
        return 5;
    else if (user == "user6")
        return 6;
    else if (user == "user7")
        return 7;
    else if (user == "user8")
        return 8;
    else
        return 0;//û��ƥ��ɹ�������0��ʾ�û������ڡ�
}


/**
 * @brief ��鵱ǰ�û����ļ��Ķ�дȨ��
 *
 * @param filename
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @return int
 */
int checkFileAuth(const string& fileName, FileSystem *fileSystem, int cur_SFD, string user) {
    int pos = -1;//��ʼ������ pos�����ڱ����ļ���Ŀ¼���е�λ��
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++) {//������ǰĿ¼���е��ļ���
        if (fileName == (*fileSystem).sfd[cur_SFD].sfdVec[i].name) {//����������ļ��� fileName ƥ����ļ���
            pos = i;//���ҵ��� fileName ƥ�䣬����λ�ñ����ڱ��� pos �У�������ѭ����
            break;
        }
    }
    if (pos == -1)
        return -2;//��� pos ��ȻΪ -1����ʾδ�ҵ��� fileName ƥ����ļ������ -2����ʾ�ļ������ڡ�
    int cur_inode = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;//�ҵ����ļ����Ӧ�� i �ڵ�ţ������ڱ��� cur_inode �С�
    if ((*fileSystem).iNode[cur_inode].type == 1)        //1��ʾ��ǰi�����Ŀ¼
        return -3;//���� -3����ʾ�޷���Ŀ¼���ж�д������
    int use = checkUser(user) - 1;
    return (*fileSystem).iNode[cur_inode].auth[use];//���ص�ǰ�û����ļ��Ķ�дȨ�ޣ������û���� use ���ļ��� i �ڵ��в��Ҷ�Ӧ��Ȩ��ֵ������ 0��Ȩ��1��Ȩ��
}


/**
 * @brief ��鵱ǰ�û���Ŀ¼�Ķ�дȨ��
 *
 * @param filename
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @param iNode
 * @return int
 */
int checkDirAuth(const string& fileName, FileSystem* fileSystem, int cur_SFD, string user, int* iNode){
    int pos = -1;
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){   //��鵱ǰĿ¼���Ƿ����
        if (fileName == (*fileSystem).sfd[cur_SFD].sfdVec[i].name){
            pos = i;
            break;
        }
    }
    if (pos != -1)//pos������-1����ʾָ�����ļ����Ѿ������ڵ�ǰĿ¼�У���������-2��ʾȨ�޼��ʧ��
        return -2;

    int cur_inode = getInodeNum(iNode, *fileSystem, cur_SFD);       //��õ�ǰĿ¼��i����
    int use = checkUser(user);
    if (use == (*fileSystem).iNode[cur_inode].id)   //����Ƿ���Ȩ��,����1��ʾ��Ȩ�ޡ�      ����0��ʾ��Ȩ�ޡ�
        return 1;
    return 0;
}

/**
 * @brief �ǳ�
 *
 * @param user
 * @param fileSystem
 * @param iNode
 * @param SFDBlock
 * @param diskBlock
 */
void logout(User& user, FileSystem fileSystem, int* iNode, int* SFDBlock, int* diskBlock){
    exitSystem(fileSystem, iNode, SFDBlock, diskBlock);
    user.userName = "";
}

