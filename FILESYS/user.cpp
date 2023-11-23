
#include "FILE.h"
string userName[8] = {"user1", "user2", "user3" ,"user4","user5", "user6", "user7", "user8"};
string pwd[8] = {"user1","user2","user3","user4","user5","user6","user7","user8"};
/**
 * @brief 用户登录
 *
 * @param user
 */
void login(User& user){
    MessageBox(nullptr, TEXT("欢迎使用文件系统！"), TEXT("WELCOME"), MB_OK); //消息盒子
    system("cls");
    setFontColor(11);
    cin.clear();//清除 cin 对象的错误状态标志。
    cin.sync(); //清除缓存区的数据流 cin.ignore(std::numeric_limits<int>::max(),'\n');
    while (true){//进入一个无限循环，要求用户输入用户名，并进行相应的处理
        setFontColor(15);
        cout << "请登录文件系统(输入exit退出文件系统): ";
        cin >> user.userName;
        if (user.userName == "exit"){
            setFontColor(9);
            cout << "Bye~\n";
            Sleep(1000);
            exit(0);
        }
        int res = checkUser(user.userName);//调用checkUser函数检查用户是否存在。
        if (!res){
            setFontColor(12);
            cout << "The user does not exist, please re-enter\n";
            continue;//如果用户不存在，显示错误消息，并重新要求用户输入用户名。
        }else{
            setFontColor(15);
            string password="";
            cout << "请输入密码: ";
            char c;
            while((c=getch())!=13) password+=c; //读取用户的键盘输入并判断是否等于 ASCII 值为 13 的回车键。
            if(password != pwd[res-1]){
                setFontColor(12);
                cout << "\nIncorrect password !!!\n";
                continue;
            }
        }
        for(int i = 0;i < NOFILE;i++){
            user.uOpenFile.SysOFId[i] = -1;//将 user 对象的 uOpenFile 成员变量中的 SysOFId 数组的所有元素设置为 -1，表示用户打开的文件标识符都未被使用
        }
        setFontColor(10);
        cout << "\nSuccessful landing, Press enter to access the file system..." << endl;
        getchar();
        getchar();//读取两次回车键输入，用于等待用户按下回车键继续
        break;
    }

}

/**
 * @brief 判断登录用户
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
        return 0;//没有匹配成功，返回0表示用户不存在。
}


/**
 * @brief 检查当前用户对文件的读写权限
 *
 * @param filename
 * @param fileSystem
 * @param cur_SFD
 * @param user
 * @return int
 */
int checkFileAuth(const string& fileName, FileSystem *fileSystem, int cur_SFD, string user) {
    int pos = -1;//初始化变量 pos，用于保存文件在目录项中的位置
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++) {//遍历当前目录项中的文件项
        if (fileName == (*fileSystem).sfd[cur_SFD].sfdVec[i].name) {//查找与给定文件名 fileName 匹配的文件。
            pos = i;//如找到与 fileName 匹配，则将其位置保存在变量 pos 中，并跳出循环。
            break;
        }
    }
    if (pos == -1)
        return -2;//如果 pos 仍然为 -1，表示未找到与 fileName 匹配的文件项，返回 -2，表示文件不存在。
    int cur_inode = (*fileSystem).sfd[cur_SFD].sfdVec[pos].id;//找到的文件项对应的 i 节点号，保存在变量 cur_inode 中。
    if ((*fileSystem).iNode[cur_inode].type == 1)        //1表示当前i结点是目录
        return -3;//返回 -3，表示无法对目录进行读写操作。
    int use = checkUser(user) - 1;
    return (*fileSystem).iNode[cur_inode].auth[use];//返回当前用户对文件的读写权限，根据用户编号 use 在文件的 i 节点中查找对应的权限值并返回 0无权限1有权限
}


/**
 * @brief 检查当前用户对目录的读写权限
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
    for (int i = 0; i < (*fileSystem).sfd[cur_SFD].sfdVec.size(); i++){   //检查当前目录下是否存在
        if (fileName == (*fileSystem).sfd[cur_SFD].sfdVec[i].name){
            pos = i;
            break;
        }
    }
    if (pos != -1)//pos不等于-1，表示指定的文件名已经存在于当前目录中，函数返回-2表示权限检查失败
        return -2;

    int cur_inode = getInodeNum(iNode, *fileSystem, cur_SFD);       //获得当前目录的i结点号
    int use = checkUser(user);
    if (use == (*fileSystem).iNode[cur_inode].id)   //检查是否有权限,返回1表示有权限。      返回0表示无权限。
        return 1;
    return 0;
}

/**
 * @brief 登出
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

