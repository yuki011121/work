
#include "FILE.h"

struct diskBlock_iNode {
    int id;                //���̿��
    int iNode;            //i�ڵ��
    int color;           //��ɫ
};
int flag = 1;

/**
 * @brief ����
 *
 */
void help() {
    setFontColor(10);
    cout << "������ʾ" << endl;
    cout << "\t�ļ�/Ŀ¼����" << endl;
    cout << "\t\t- ����:       rname <f1> <f2> " << endl;
    cout << "\t\t- ����:       link <name>" << endl;
    cout << "\t\t- ����:       find <name>" << endl;
    cout << "\t\t- ����:       cut <name>" << endl;
    cout << "\t\t- ����:       copy <name> " << endl;
    cout << "\t\t- ճ��:       paste" << endl;
    cout << "\tĿ¼����" << endl;
    cout << "\t\t- ����Ŀ¼:    mkdir <name> " << endl;
    cout << "\t\t- ��ʾĿ¼:    ls" << endl;
    cout << "\t\t- �л�Ŀ¼:    cd <name> " << endl;
    cout << "\t\t- ���ظ�Ŀ¼:   cd/ " << endl;
    cout << "\t\t- ɾ��Ŀ¼:    deld <name> " << endl;
    cout << "\t\t- �����ϼ�Ŀ¼: cd.." << endl;
    cout << "\t�ļ�����" << endl;
    cout << "\t\t- ���ļ�:    open <name>" << endl;
    cout << "\t\t- �ر��ļ�:    close <name>" << endl;
    cout << "\t\t- �����ļ�:    creat <name>" << endl;
    cout << "\t\t- ɾ���ļ�:    delf <name>" << endl;
    cout << "\t\t- ��д�ļ�:    write <name>" << endl;
    cout << "\t\t- ��ȡ�ļ�:    read <name>" << endl;
    cout << "\t��������" << endl;
    cout << "\t\t- ����:       clear" << endl;
    cout << "\t\t- ��ʽ��:      format" << endl;
    cout << "\t\t- ע����¼:    logout" << endl;
    cout << "\t\t- λʾͼ:      print" << endl;
    cout << "\t\t- �Զ���ȫ:    Tab" << endl;
    cout << "\t\t- �˳�ϵͳ:    exit" << endl;
    cout << "\t\t- ��ʾ����:    help" << endl;
    cout << " " << endl;
}

/**
 * @brief ����������������ʵ�ִ󲿷������������
 *
 * @param user
 * @param cur_SFD
 * @param staSFD
 * @param fileSystem
 * @param copy_flag
 * @param iNode
 * @param diskBlock
 * @param SFDBlock
 * @param copySFD
 */
void display(User &user, int *cur_SFD, stack<int> *staSFD, SysOpenFile *sysOFile,
             FileSystem *fileSystem, int *copy_flag, int *iNode,
             int *diskBlock, int *SFDBlock, SingleSFD *copySFD) {
    system("cls");
    help();
    int getdir = 0; //��Ŀ¼�����Ŀ¼������
    string in1, filename, str = user.userName + "@file\\";
    while (true) {
        int tmp = -1;
        while (true) {
            setFontColor(14);
            cout << endl << str << ">";
            cin.sync();//��ջ�����������
            in1.clear();
            cin_command(in1, flag);
            if (in1.empty())continue;
            for (int i = 0; i < in1.size(); i++) {
                if (in1[i] >= 'A' && in1[i] <= 'Z') {
                    in1[i] = in1[i] - 'A';
                    in1[i] = in1[i] + 'a';     //��дת��ΪСд
                }
            }
            tmp = checkIn(in1); //�������Ƿ�Ϸ�
            if (tmp == 1 && flag) {
                getchar();
                cin.sync();
            } else if (!flag)flag = 1;
            if (tmp != 0)break;

            setFontColor(12);
            cout << endl << "ϵͳ�޴�����!\n������help��ȡ����!" << endl;
        }
        //����
        if (in1 == "clear") {
            system("cls");
        }
            //����
        else if (in1 == "help") {
            help();
        }
            //�˳�ϵͳ
        else if (in1 == "exit") {
            logout(user, *fileSystem, iNode, SFDBlock, diskBlock);
            setFontColor(10);
            cout << "�˳��ɹ���ллʹ�ã�\n";
            exit(0);
        }
            //�˳���ǰ�û�
        else if (in1 == "logout") {
            user.userName = "";
            setFontColor(10);
            cout << "�˳��ɹ�!\n";
            system("cls");
            login(user);
            //init();
            cout << "��ӭʹ���ļ�ϵͳ��\n" << endl;
            (*cur_SFD) = 0;
            setFontColor(14);
            str =user.userName + "@file\\";
        } else if (in1 == "ls") {
            setFontColor(11);
            showSFD(*fileSystem, *cur_SFD);
            continue;
        } else if (in1 == "display") {
            print(*fileSystem, iNode, diskBlock, SFDBlock);
        }
            //��ʽ����ǰ�û�
        else if (in1 == "format") {
            if (user.userName.empty()) { //�û���Ϊ��
                setFontColor(10);
                cout << "���Ƚ��е�¼���ٽ��и�ʽ����\n";
                continue;
            }
            setFontColor(12);
            cout << "���棺��ʽ����ɾ�����û��������ļ����ݡ�\n" << "����������Y�������˳���������N�� ";
            string strtmp;
            while (true) {
                cin >> strtmp;
                if (strtmp == "N" || strtmp == "n")
                    break;
                else if (strtmp != "Y" && strtmp != "y") {

                    setFontColor(12);
                    cout << "���벻�Ϸ�������������\n";
                    continue;
                }
                break;
            }
            if (strtmp == "N" || strtmp == "n")
                continue;
            (*cur_SFD) = checkUser(user.userName);
            formatUser(fileSystem, *cur_SFD, iNode, SFDBlock, diskBlock, user.userName);
            (*cur_SFD) = 0;


            str = user.userName + "@file\\";

            setFontColor(10);
            cout << "��ʽ���ɹ���\n";
        }
            //�����ļ�
        else if (in1 == "create") {
            filename.clear();
            //cin >> filename;
            //cin.sync();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {//���� flag ��ֵ���ж��Ƿ���Ҫ������뻺����

                getchar();
                cin.sync();
            } else flag = 1;
            int cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD); //��ȡ��ǰĿ¼�������� 
            if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {
                setFontColor(12);
                cout << "����ʧ�ܣ���û���ڸ�Ŀ¼�´����ļ���Ȩ��" << endl;
                continue;
            }
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];//��������ļ����е�·����Ϣ��ȡ��Ŀ���ļ����ĵ�����ʽ���洢�� filename3 ������
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ��޷������ļ��������´����ļ���"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�������ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];//ͨ����ת filename3 ���ַ�˳�򣬵õ�Ҫ�������ļ������洢�� filename4 �����С�
            }
            int tmpauth = checkDirAuth(filename4, fileSystem, *cur_SFD, user.userName, iNode);
            if (tmpauth == -2) {
                setFontColor(12);
                cout << "���ļ����Ѵ��ڣ������ļ�ʧ�ܣ�\n";
                continue;
            }
            //cout<<filename.length()<<endl;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {//������� '\\' �ַ����Ѿ��������ַ���ĩβ�����ʾ�Ѿ���ȡ��һ��Ŀ¼��
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        int tmpauth = checkDirAuth(filename2, fileSystem, *cur_SFD, user.userName, iNode);//����Ŀ¼���Ƿ��Ѿ�����
                        if (tmpauth == -2) {
                            //cout << "�Ѵ��ڵ��ļ�����Ŀ¼��������Ŀ¼ʧ�ܣ�\n";
                            if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                //cout << "�����ɹ���\n"; //���Ŀ¼���Ѵ��ڣ�������Ŀ¼
                                (*staSFD).push(*cur_SFD);
                            }
                        } else if (tmpauth == 0) { 
                            setFontColor(12);
                            cout << "����ʧ�ܣ��������д�����Ŀ¼Ȩ�ޣ�\n";
                        } else {
                            if (createDir(filename2, fileSystem, user.userName, iNode, SFDBlock, *cur_SFD)){
                                setFontColor(10);
                                cout << "�����ɹ���\n";
                                if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                    //cout << "�����ɹ���\n";
                                    (*staSFD).push(*cur_SFD);
                                }
                            }
                        }
                        filename2 = "";
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if (createFile(filename4, fileSystem, *cur_SFD, iNode, user.userName, diskBlock, SFDBlock)) {
                setFontColor(10);
                cout << "�Ƿ�����д�����ݣ�\n" << "����д��������Y���Ժ�д��������N�� ";
                string strtmp;
                while (true) {
                    fflush(stdin);
                    cin >> strtmp;
                    if (strtmp == "Y" || strtmp == "y") {
                        writeFile(filename, fileSystem, *cur_SFD, diskBlock);
                        break;
                    } else if (strtmp == "N" || strtmp == "n")
                        break;
                    else {
                        setFontColor(12);
                        cout << "���벻�Ϸ�������������\n";
                    }
                }
            }

        }
            //���ļ�
        else if (in1 == "read") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ���ȡ�ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            int index = 0;
            if (!hasOpen(user, sysOFile, filename4, index)) {
                setFontColor(12);
                cout << "��ȡʧ�ܣ��ļ�δ�򿪻򲻴��ڣ���򿪻򴴽������ԣ�\n";
                continue;
            }
            int cur_iNode = sysOFile[user.uOpenFile.SysOFId[index] - 1].iId;
            int usr = checkUser(user.userName) - 1;
            readFile(filename4, *fileSystem, *cur_SFD);
            cout << endl;
            if ((*fileSystem).iNode[cur_iNode].type == 1) {
                setFontColor(12);
                cout << "��ȡʧ�ܣ���ȡ���ļ�ΪĿ¼�ļ���\n";
                continue;
            } else if ((*fileSystem).iNode[cur_iNode].auth[usr] == -1) {
                setFontColor(12);
                cout << "��ȡʧ�ܣ��������ж�ȡȨ�ޣ�\n";
                continue;
            } else {
                readFile(filename4, *fileSystem, *cur_SFD);
                cout << endl;
            }
        }    //���ļ�
        else if (in1 == "open") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ����ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            openFile(filename4, *fileSystem, *cur_SFD, user, sysOFile);
        }    //�ر��ļ�
        else if (in1 == "close") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ��ر��ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            closeFile(filename4, *fileSystem, *cur_SFD, user, sysOFile);
        }
            //����Ŀ¼
        else if (in1 == "mkdir") {
            filename.clear();
            //cin >> filename;
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ������ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int tmpauth = checkDirAuth(filename4, fileSystem, *cur_SFD, user.userName, iNode);
            if (tmpauth == -2) {
                setFontColor(12);
                cout << "�Ѵ��ڵ��ļ�����Ŀ¼��������Ŀ¼ʧ�ܣ�\n";
                continue;
            }
            //cout<<filename.length()<<endl;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    //cout<<filename2<<endl;
                    str += "\\" + filename2;
                    //cout<<str<<endl;
                    int tmpauth = checkDirAuth(filename2, fileSystem, *cur_SFD, user.userName, iNode);
                    if (tmpauth == -2) {
                        //setFontColor(12);
                        //cout << "�Ѵ��ڵ��ļ�����Ŀ¼��������Ŀ¼ʧ�ܣ�\n";
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            //setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                        }
                    } else if (tmpauth == 0) {
                        setFontColor(12);
                        cout << "����ʧ�ܣ��������д�����Ŀ¼Ȩ�ޣ�\n";
                    } else {
                        if (createDir(filename2, fileSystem, user.userName, iNode, SFDBlock, *cur_SFD)){
                            setFontColor(10);
                            cout << "�����ɹ���\n";
                            if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                //setFontColor(6);
                                //cout << "�����ɹ���\n";
                                (*staSFD).push(*cur_SFD);
                            }
                        }
                    }
                    filename2 = "";
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
        }
            //ɾ��Ŀ¼
        else if (in1 == "deld") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            int cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD);
            int use = checkUser(user.userName);
            if (use != (*fileSystem).iNode[cur_inode].id) {
                setFontColor(12);
                cout << "ɾ��ʧ�ܣ���������ɾ��Ŀ¼Ȩ�ޣ�\n";
                continue;
            }
            else {
                string filename2="";
                string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
                for(int checki=filename.length()-1;checki>=0;checki--){
                    if(filename[checki]=='\\'){
                        break;
                    }
                    else{
                        filename3 = filename3 + filename[checki];
                    }
                }
                if(filename3 == ""){
                    setFontColor(12);
                    cout<< "�ļ���Ϊ�գ�ɾ��Ŀ¼ʧ�ܣ�"<<endl;
                    continue;
                }
                string filename4="";          //Ҫ�����ļ���
                for(int checki=filename3.length()-1;checki>=0;checki--){
                    filename4 = filename4 + filename3[checki];
                }
                int flag_out=1;
                for(int checki=0;checki<=filename.length();checki++){
                    if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                        if(filename2 == filename4){
                            break;
                        }
                        else{
                            //cout<<filename2<<endl;
                            str += "\\" + filename2;
                            //cout<<str<<endl;
                            if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                setFontColor(6);
                                //cout << "�����ɹ���\n";
                                (*staSFD).push(*cur_SFD);
                                filename2 = "";
                            }
                            else{
                                flag_out=0;
                                setFontColor(6);
                                //cout << "����ʧ�ܣ�\n";
                                int len = filename2.size() + 1;
                                int pos = str.find("\\" + filename2);
                                str.erase(pos, len);
                                filename2 = "";
                                break;
                            }
                        }
                    }
                    else if( filename[checki]!='\\' ) {
                        filename2 = filename2 + filename[checki];
                        //cout<<filename2<<endl;
                    }
                }
                int pos = -1;
                for (int i = 0; i < (*fileSystem).sfd[(*cur_SFD)].sfdVec.size(); i++) {
                    if (filename4 == (*fileSystem).sfd[(*cur_SFD)].sfdVec[i].name) {
                        pos = i;
                        break;
                    }
                }
                if (pos == -1) {
                    setFontColor(12);
                    cout << "ɾ��ʧ�ܣ�Ŀ¼�������ڣ�\n";
                    continue;
                }
                int cur_inode = (*fileSystem).sfd[(*cur_SFD)].sfdVec[pos].id;
                if ((*fileSystem).iNode[cur_inode].type == 0) {       //1��ʾ��ǰi������ļ�
                    setFontColor(12);
                    //cout << "ɾ��ʧ�ܣ�����Ϊ�ļ�����\n";
                    continue;
                }
                if(flag_out==0){
                    continue;
                }
                if (deleteDir(filename4, fileSystem, *cur_SFD, iNode, SFDBlock, diskBlock, user.userName)) {
                    setFontColor(10);
                    cout << "ɾ���ɹ���\n";
                }
            }
        }
            //ɾ���ļ�
        else if (in1 == "delf") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            int index = 0;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ�ɾ���ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            if (hasOpen(user, sysOFile, filename4, index)) {
                setFontColor(12);
                cout << "ɾ��ʧ�ܣ��ļ����ڱ��򿪣���رպ����ԣ�\n";
                continue;
            }
            int cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD);
            if (freeFile(filename4, fileSystem, *cur_SFD, user.userName, iNode, diskBlock, SFDBlock)) {
                setFontColor(10);
                cout << "ɾ���ļ��ɹ���\n";
            }
            if ((*fileSystem).iNode[cur_inode].type == 1) {
                setFontColor(12);
                //cout << "ɾ��ʧ�ܣ�����ΪĿ¼����\n";
                continue;
            }else if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {
                setFontColor(12);
                cout << "ɾ��ʧ�ܣ���û���ڸ�Ŀ¼��ɾ���ļ���Ȩ��" << endl;
                continue;
            }

        }
            //������һ��Ŀ¼
        else if (in1 == "cd"){
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag){

                getchar();
                cin.sync();
            }
            else flag = 1;
            string filename2="";
            //cout<<filename.length()<<endl;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    //cout<<filename2<<endl;
                    if(filename2 == ""){
                        continue;
                    }
                    str += "\\" + filename2;
                    //cout<<str<<endl;
                    if (goNextDir(filename2, *fileSystem, cur_SFD)){
                        setFontColor(6);
                        //cout << "�����ɹ���\n";
                        (*staSFD).push(*cur_SFD);
                        filename2 = "";
                    }
                    else{
                        setFontColor(6);
                        //cout << "����ʧ�ܣ�\n";
                        int len = filename2.size() + 1;
                        int pos = str.find("\\" + filename2);
                        str.erase(pos, len);
                        filename2 = "";
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
        }
            //д�ļ�
        else if (in1 == "write") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {

                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ�д�ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            int index = 0;
            if (!hasOpen(user, sysOFile, filename4, index)) {
                setFontColor(12);
                cout << "д�ļ�ʧ�ܣ��ļ�δ�򿪻򲻴��ڣ���򿪻򴴽������ԣ�\n";
                continue;
            }
            int cur_iNode = sysOFile[user.uOpenFile.SysOFId[index] - 1].iId;
            int usr = checkUser(user.userName) - 1;
            if ((*fileSystem).iNode[cur_iNode].type == 1) {
                setFontColor(12);
                cout << "д�ļ�ʧ�ܣ���д���ļ�ΪĿ¼�ļ���\n";
                continue;
            } else if ((*fileSystem).iNode[cur_iNode].auth[usr] == -1 ||
                       (*fileSystem).iNode[cur_iNode].auth[usr] == 0) {
                setFontColor(12);
                cout << "д�ļ�ʧ�ܣ���������д���ļ���Ȩ�ޣ�\n";
                continue;
            } else {
                writeFile(filename4, fileSystem, *cur_SFD, diskBlock);
            }
        }
            //�����ļ�
        else if (in1 == "copy") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            *copy_flag = 1;//copy
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ������ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            if (copyContext(filename4, *fileSystem, *cur_SFD, copySFD, copy_flag)) {
                setFontColor(10);
                cout << "���Ƴɹ�\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "����ʧ��\n";
            }
        } else if (in1 == "cut") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            *copy_flag = 2;//cut
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ�д�ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            if (cutContext(filename4, copySFD, fileSystem, *cur_SFD)) {
                setFontColor(10);
                cout << "���гɹ�\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "����ʧ��\n";
            }
        } else if (in1 == "link") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            *copy_flag = 3;//link
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//��·�����˵����õ�Ŀ���ļ����ĵ�������
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "�ļ���Ϊ�գ�д�ļ�ʧ�ܣ�"<<endl;
                continue;
            }
            string filename4="";          //Ҫ�����ļ���
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int flag_out=1;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            setFontColor(6);
                            //cout << "�����ɹ���\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "����ʧ�ܣ�\n";
                            int len = filename2.size() + 1;
                            int pos = str.find("\\" + filename2);
                            str.erase(pos, len);
                            filename2 = "";
                            break;
                        }
                    }
                }
                else if( filename[checki]!='\\' ) {
                    filename2 = filename2 + filename[checki];
                    //cout<<filename2<<endl;
                }
            }
            if(flag_out==0){
                continue;
            }
            if (copyContext(filename4, *fileSystem, *cur_SFD, copySFD, copy_flag)) {

                setFontColor(10);
                cout << "��׼��������\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "����ʧ��\n";
            }
        }
            //ճ���ļ�
        else if (in1 == "paste") {
            if (pasteContext(*copy_flag, *copySFD, *cur_SFD, fileSystem, user.userName, iNode, diskBlock, SFDBlock))
                cout << "ճ���ɹ�\n";
        }
            //�����ϼ�Ŀ¼
        else if (in1 == "cd..") {
            if ((*staSFD).top() == 0) {
                str = user.userName + "@file\\";
                *cur_SFD = 0;
                continue;
            }
            int pos = -1, len = 0;
            for (int k = str.size() - 1; k >= 0; k--) {
                if (str[k] == '\\') {
                    pos = k;
                    break;
                }
                len++;
            }
            if (pos == -1) {
                str = user.userName + "@file\\";
                *cur_SFD = 0;
                continue;
            }
            str.erase(pos, len + 1);
            (*staSFD).pop();
            *cur_SFD = (*staSFD).top();
        }
            //���ظ�Ŀ¼
        else if (in1 == "cd/") {
            str = user.userName + "@file\\";
            *cur_SFD = 0;
            while (!(*staSFD).empty()) {
                (*staSFD).pop();
            }
        }
            //else if (in1 == "signin"){}
        else if (in1 == "rname") {
            string rname;
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            cin >> rname;
            cin.sync();
            int i, cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD);    //��õ�ǰĿ¼��i�ڵ��
            if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {    //�жϵ�¼�û���i�ڵ������û��Ƿ���ͬ
                setFontColor(12);
                cout << "����ʧ�ܣ���û���ڸ�Ŀ¼�¸�����Ȩ��" << endl;
                continue;
            }
            else {
                for (i = 0; i < (*fileSystem).sfd[*cur_SFD].sfdVec.size(); i++) {
                    if ((*fileSystem).sfd[*cur_SFD].sfdVec[i].name == filename) {    //�����ļ�ϵͳĿ¼����ÿ��Ŀ¼����ļ������ҵ����˳�ѭ��
                        break;
                    }
                }
                if (i != (*fileSystem).sfd[*cur_SFD].sfdVec.size()) {    //�ҵ�����Ҫ���ĵ��ļ���
                    (*fileSystem).sfd[*cur_SFD].sfdVec[i].name = rname;    //������
                    setFontColor(10);
                    cout << "�����ɹ�\n";
                }
                else {
                    setFontColor(12);
                    cout << "δ�ҵ�ָ���ļ���Ŀ¼��\n";
                }
            }
        }
        else if (in1 == "find") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {

                getchar();
                cin.sync();
            } else flag = 1;
            setFontColor(15);
            cout << "\n�ļ���\t\t·��" << endl;
            setFontColor(11);
            if (str.size() < 12)find_filedir(str.substr(11), filename, *fileSystem, *cur_SFD);
            else find_filedir("\\" + str.substr(12), filename, *fileSystem, *cur_SFD);
        }
        else if (in1 == "print") {
            setFontColor(14);
            cout << "������鿴����ѡ��\n";
            cout << endl;
            cout << "1:λʾͼ��Ϣ             2:���̿�i�����Ϣ\n";
            cout << "\n";
            cout << "3:��ϸ��Ϣ               4�����д��̿���Ϣ\n";
            cout << "\n";
            string in2;
            cin >> in2;
            if (in2 == "1") {
                system("cls");
                setFontColor(14);
                cout << "�������λʸͼ\n" << endl;
                for (int i = 0; i < (*fileSystem).superBlock.i_node; i++) {
                    if (iNode[i] == 0) setFontColor(12);
                    else setFontColor(10);
                    cout << " " << iNode[i] << " ";
                    if ((i + 1) % 16 == 0) cout << endl;
                }
                cout << endl << endl << endl;
                setFontColor(14);
                cout << "���̿�λʸͼ\n" << endl;
                for (int i = 0; i < (*fileSystem).superBlock.disk; i++) {
                    if (diskBlock[i] == 0) setFontColor(12);
                    else setFontColor(10);
                    cout << " " << diskBlock[i] << " ";
                    if ((i + 1) % 16 == 0) cout << endl;
                }
                cout << endl << endl << endl;
                setFontColor(14);
                cout << "sfdλʸͼ\n" << endl;
                for (int i = 0; i < (*fileSystem).superBlock.sfd; i++) {
                    if (SFDBlock[i] == 0) setFontColor(12);
                    else setFontColor(10);
                    cout << " " << SFDBlock[i] << " ";
                    if ((i + 1) % 16 == 0) cout << endl;
                }
                cout << endl;
                setFontColor(14);
            }
            else if (in2 == "2") {
                system("cls");
                printDiskBitmap(*fileSystem, iNode);
            }
            else if (in2 == "3") {
                system("cls");
                print(*fileSystem, iNode, diskBlock, SFDBlock);
            }
            else if (in2 == "4") {
                system("cls");
                printFreeDiskGroup1(*fileSystem);
                FreeDiskGroup(*fileSystem, diskBlock);
            }
            else { cout << "����ѡ������\n"; }


            }
        else {
                setFontColor(12);
                //cout << fileSystem.superBlock.freeDisk << "  " << fileSystem.superBlock.freei_node << "  " << fileSystem.superBlock.free_SFD << endl;
                cout << "�޴�����޴˹��ܣ�\n���๦�ܣ������ڴ���" << endl;
                }
    }
}

/**
 * ����������ɫ
 * @param color 10:��ɫ  14:��ɫ   12:��ɫ
 */
void setFontColor(int color) {
    if (color == 14) color++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);  //��׼������豸�ľ��������������Ļ�������ľ����
}


/**
 * @brief ������������Ƿ�����Լ�ָ�������
 *
 * @param in
 * @return int
 */
int checkIn(const string& in) {
    if (in == "paste" || in == "print" || in == "clear" || in == "help" || in == "exit"
        || in == "format" || in == "logout" || in == "cd.." || in == "ls" || in == "signin" || in == "cd/" ||
        in == "display")
        return 1;
    else if (in == "cut" || in == "link" || in == "copy" || in == "find"
        || in == "create" || in == "read" || in == "mkdir" || in == "deld"
        || in == "delf" || in == "cd" || in == "write" || in == "open" || in == "close")
        return 2;
    else if (in == "rname")
        return 3;
    else
        return 0;
}

/**
 * �ж��ļ��Ƿ��
 * @param user
 * @param sysOFile
 * @param filename
 * @param index
 * @return
 */
bool hasOpen(User& user, SysOpenFile* sysOFile, string filename, int& index) {
    for (int i = 0; i < NOFILE; i++) {  //NOFILE:ÿ���û����ɴ�20���ļ������û����ļ�������
        if (user.uOpenFile.SysOFId[i] != -1) {  //ϵͳ�����������Ѵ򿪸��ļ�
            //cout << sysOFile[user.uOpenFile.SysOFId[i] - 1].fileName << endl;
            if (sysOFile[user.uOpenFile.SysOFId[i] - 1].fileName == filename) {
                index = i;    //�����򿪵��ļ������û��ļ����ļ�����ָ��ϵͳ���ļ�����ļ�����ͬ�򷵻ظ��ļ���������ʾ�ý����Ѵ�
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief
 *
 */
void printFreeDiskGroup() {  //�����������ǰ�����鳤��
    int group[12] = { 10 };
    cout << " ------        ------" << endl;
    printf("|  %2d  |  --->|  %2d  |\n", group[0], group[1]);
    cout << " ------   |    ------" << endl;
    printf("|  %2d  |---   |  %2d  |\n", group[2], group[3]);
    cout << " ------        ------" << endl;
    printf("|  %2d  |      |  %2d  |\n", group[4], group[5]);
    cout << " ------        ------" << endl;
    printf("|  %2d  |      |  %2d  |\n", group[6], group[7]);
    cout << " ------        ------" << endl;
    printf("|  %2d  |      |  %2d  |\n", group[8], group[9]);
    cout << " ------        ------" << endl;
    printf("|  %2d  |      |  %2d  |\n", group[10], group[11]);
    cout << " ------        ------" << endl;
}

void print(FileSystem fileSystem, int* iNode, int* diskBlock, int* SFDBlock) {  //���i�ڵ㣬���̿飬Ŀ¼��ȫ����Ϣ
    cout << "�ڼ���i�ڵ�\t" << "�����û�\t����\t��ӦĿ¼id\tȨ��\t  ���ڵĴ���/Ŀ¼��" << endl;
    setFontColor(10);  //��ɫ
    for (int i = 0; i < 128; i++) {
        if (!iNode[i]) {
            cout << "    " << i << "\t\t" << fileSystem.iNode[i].id << "\t\t" << fileSystem.iNode[i].type << "\t   "
                << fileSystem.iNode[i].sfd_id << "\t  ";
            for (int j = 0; j < 8; j++) {
                if (fileSystem.iNode[i].auth[j] == -1)
                    cout << fileSystem.iNode[i].auth[j];
                else
                    cout << " " << fileSystem.iNode[i].auth[j];
            }
            cout << "\t";
            if (fileSystem.iNode[i].type == 0) {

                cout << fileSystem.iNode[i].diskBlockId << endl;    //�ļ����ӡ�����ļ���ռ���̿��id�ŵ�������
            }
            else {
                cout << fileSystem.iNode[i].sfd_id << endl;    //Ŀ¼���ӡ��i����Ӧ��Ŀ¼id
            }
            /*
            if (fileSystem.iNode[i].type == 1){
            int number = fileSystem.iNode[i].sfd_id;
            if (fileSystem.sfd[number].sfdVec.size() != 0)
            cout << fileSystem.sfd[number].sfdVec[0].name;
            else cout << "Ϊ�գ�";
            }*/
        }
    }
    setFontColor(14);
    cout << endl;
    cout << "�ڼ������̿�\t" << "����\t" << "\t����" << endl;
    setFontColor(10);
    for (int i = 0; i < 512; i++) {
        if (!diskBlock[i]) {
            cout << "    " << i << "\t\t " << fileSystem.diskBlock[i].strNum << "\t\t" << fileSystem.diskBlock[i].file
                << endl;
        }
        if (fileSystem.diskBlock[i].strNum == 999) cout << i << "  gg" << endl;
    }
    setFontColor(14);
    cout << endl;
    cout << "�ڼ���Ŀ¼��\t" << "����\t" << "���ݣ���Ӧi�ڵ��ţ�" << endl;
    setFontColor(10);
    for (int i = 0; i < 512; i++) {
        if (!SFDBlock[i]) {
            cout << "   " << i << "  \t \t " << fileSystem.sfd[i].sfdNum << "     ";
            for (int j = 0; j < fileSystem.sfd[i].sfdVec.size(); j++)
                cout << fileSystem.sfd[i].sfdVec[j].name << " (" << fileSystem.sfd[i].sfdVec[j].id << ")  ";
            cout << endl;
        }

    }
    setFontColor(14);

}

void FreeDiskGroup(FileSystem fileSystem, int* diskBlock) {  //������������鳤����Ϣ
    for (int i = 0; i < 512; i++) {
        if (fileSystem.diskBlock[i].file.size() > 0 && diskBlock[i] == 1) {
            setFontColor(10);
            cout << "�鳤���� : ";

            cout << i << " ������: ";
            setFontColor(14);
            cout << fileSystem.diskBlock[i].file << endl;

        }
    }
}

void printDiskBitmap(FileSystem fileSystem, int iNode[]) {  //������̿�λʾͼ
    vector<vector<diskBlock_iNode>> fileBlocks;
    for (int i = 0, k = 1; i < 128; i++) {
        if (iNode[i] == 0) {
            if (fileSystem.iNode[i].type == 0) {    //�ļ�
                vector<diskBlock_iNode> fileBlock;
                diskBlock_iNode indexNode;
                indexNode.id = fileSystem.iNode[i].diskBlockId;
                indexNode.iNode = i;
                if (k % 256 == 0)
                    k++;
                indexNode.color = k % 256;
                fileBlock.push_back(indexNode);
                int* iaddr = getIaddr(fileSystem.iNode[i].diskBlockId, fileSystem);
                int flag = 1;
                for (int j = 0; j < 10; j++) {
                    if (iaddr[j] == -1) {
                        flag = 0;
                        break;
                    }
                    diskBlock_iNode tmp;
                    tmp.id = iaddr[j];
                    tmp.iNode = i;
                    tmp.color = k % 256;
                    fileBlock.push_back(tmp);
                }
                if (flag) {
                    for (int j = 10; j < 13; j++) {
                        if (iaddr[j] == -1 || flag == 0) {
                            break;
                        }
                        else {
                            diskBlock_iNode tmp;
                            tmp.id = iaddr[j];
                            tmp.iNode = i;
                            tmp.color = k % 256;
                            fileBlock.push_back(tmp);
                            int* iaddr2 = getIaddr(iaddr[j], fileSystem);
                            for (int iaddrIndex = 0; iaddrIndex < 128; iaddrIndex++) {
                                if (iaddr2[iaddrIndex] == -1) {
                                    flag = 0;
                                    break;
                                }
                                else {
                                    diskBlock_iNode tmp;
                                    tmp.id = iaddr2[iaddrIndex];
                                    tmp.iNode = i;
                                    tmp.color = k % 256;
                                    fileBlock.push_back(tmp);
                                }
                            }
                        }
                    }
                }
                k++;
                fileBlocks.push_back(fileBlock);
            }
        }
    }
    vector<diskBlock_iNode> diskBlock_iNodes;
    for (int i = 0; i < fileBlocks.size(); i++) {
        for (int j = 0; j < fileBlocks[i].size(); j++) {
            //cout << fileBlocks[i][j].id << "\t" << fileBlocks[i][j].iNode << "\t" << fileBlocks[i][j].color << "\t\t";
            diskBlock_iNodes.push_back(fileBlocks[i][j]);
        }
        //cout << endl;
    }

    diskBlock_iNode bits[512];
    for (int i = 0; i < 512; i++) {
        bits[i].id = i;
        bits[i].color = 14;
        bits[i].iNode = -1;
    }
    for (int i = 0; i < diskBlock_iNodes.size(); i++) {
        bits[diskBlock_iNodes[i].id].color = diskBlock_iNodes[i].color;
        bits[diskBlock_iNodes[i].id].iNode = diskBlock_iNodes[i].iNode;
    }

    for (int i = 0; i < 512; i++) {
        if (i % 16 == 0) {
            setFontColor(14);
            cout << endl;
            for (int j = 0; j < 16; j++)
                cout << " ----";
            cout << endl;
        }
        setFontColor(14);
        cout << "| ";
        setFontColor(bits[i].color);
        printf("%3d", bits[i].iNode);
        setFontColor(14);
    }
    cout << endl;
    for (int j = 0; j < 16; j++)
        cout << " ----";
    cout << endl;
}

void printFreeDiskGroup1(FileSystem fileSystem) {  //��ʾ��������ǰ�����鳤��������
    int group[12] = { 0 };
    for (int ii = 0; ii < BLOCK_NUM + 1; ii++) {
        group[ii] = fileSystem.superBlock.freeDiskSta[ii];//group[0]-group[5]��ʾ���ǳ������ӿ��д��̿�ջ������
    }
    if (fileSystem.superBlock.freeDiskSta[1] != DISK_NUM) { //���п�δ�������
        int flag = 0;
        string file = fileSystem.diskBlock[fileSystem.superBlock.freeDiskSta[1]].file;  //���д��̿�ջ�д�ջ���Ĵ��̿����ݸ���file����ջ�����̿�����һ���鳤�飩
        int tmp = 0;
        for (int ii = BLOCK_NUM + 1, jj = 0; ii < 2 * BLOCK_NUM + 2, jj < file.size(); jj++) {
            if (file[jj] != ' ') {
                flag = 1;
                tmp = tmp * 10 + file[jj] - '0';
            }
            else if (flag == 1 && file[jj] == ' ') {
                group[ii] = tmp;  //��file�е����ݷֱ𸳸�group[6]-[11]
                tmp = 0;
                ii++;
                flag = 0;
            }
            else {
                continue;
            }

        }
        group[2 * BLOCK_NUM + 1] = tmp;
    }
    cout << endl;
    cout << " -------        -------" << endl;
    printf("|  %3d  |  --->|  %3d  |\n", group[0], group[6]);
    cout << " -------   |    -------" << endl;
    printf("|  %3d  |---   |  %3d  |\n", group[1], group[7]);
    cout << " -------        -------" << endl;
    printf("|  %3d  |      |  %3d  |\n", group[2], group[8]);
    cout << " -------        -------" << endl;
    printf("|  %3d  |      |  %3d  |\n", group[3], group[9]);
    cout << " -------        -------" << endl;
    printf("|  %3d  |      |  %3d  |\n", group[4], group[10]);
    cout << " -------        -------" << endl;
    printf("|  %3d  |      |  %3d  |\n", group[5], group[11]);

    cout << " -------        -------" << endl;
}