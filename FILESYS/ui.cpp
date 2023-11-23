
#include "FILE.h"

struct diskBlock_iNode {
    int id;                //磁盘块号
    int iNode;            //i节点号
    int color;           //颜色
};
int flag = 1;

/**
 * @brief 帮助
 *
 */
void help() {
    setFontColor(10);
    cout << "命令提示" << endl;
    cout << "\t文件/目录操作" << endl;
    cout << "\t\t- 更名:       rname <f1> <f2> " << endl;
    cout << "\t\t- 链接:       link <name>" << endl;
    cout << "\t\t- 查找:       find <name>" << endl;
    cout << "\t\t- 剪切:       cut <name>" << endl;
    cout << "\t\t- 复制:       copy <name> " << endl;
    cout << "\t\t- 粘贴:       paste" << endl;
    cout << "\t目录操作" << endl;
    cout << "\t\t- 创建目录:    mkdir <name> " << endl;
    cout << "\t\t- 显示目录:    ls" << endl;
    cout << "\t\t- 切换目录:    cd <name> " << endl;
    cout << "\t\t- 返回根目录:   cd/ " << endl;
    cout << "\t\t- 删除目录:    deld <name> " << endl;
    cout << "\t\t- 返回上级目录: cd.." << endl;
    cout << "\t文件操作" << endl;
    cout << "\t\t- 打开文件:    open <name>" << endl;
    cout << "\t\t- 关闭文件:    close <name>" << endl;
    cout << "\t\t- 创建文件:    creat <name>" << endl;
    cout << "\t\t- 删除文件:    delf <name>" << endl;
    cout << "\t\t- 改写文件:    write <name>" << endl;
    cout << "\t\t- 读取文件:    read <name>" << endl;
    cout << "\t其他操作" << endl;
    cout << "\t\t- 清屏:       clear" << endl;
    cout << "\t\t- 格式化:      format" << endl;
    cout << "\t\t- 注销登录:    logout" << endl;
    cout << "\t\t- 位示图:      print" << endl;
    cout << "\t\t- 自动补全:    Tab" << endl;
    cout << "\t\t- 退出系统:    exit" << endl;
    cout << "\t\t- 显示帮助:    help" << endl;
    cout << " " << endl;
}

/**
 * @brief 界面主函数，用来实现大部分输入输出功能
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
    int getdir = 0; //跨目录命令跨目录的数量
    string in1, filename, str = user.userName + "@file\\";
    while (true) {
        int tmp = -1;
        while (true) {
            setFontColor(14);
            cout << endl << str << ">";
            cin.sync();//清空缓存区数据流
            in1.clear();
            cin_command(in1, flag);
            if (in1.empty())continue;
            for (int i = 0; i < in1.size(); i++) {
                if (in1[i] >= 'A' && in1[i] <= 'Z') {
                    in1[i] = in1[i] - 'A';
                    in1[i] = in1[i] + 'a';     //大写转化为小写
                }
            }
            tmp = checkIn(in1); //查命令是否合法
            if (tmp == 1 && flag) {
                getchar();
                cin.sync();
            } else if (!flag)flag = 1;
            if (tmp != 0)break;

            setFontColor(12);
            cout << endl << "系统无此命令!\n请输入help获取帮助!" << endl;
        }
        //清屏
        if (in1 == "clear") {
            system("cls");
        }
            //帮助
        else if (in1 == "help") {
            help();
        }
            //退出系统
        else if (in1 == "exit") {
            logout(user, *fileSystem, iNode, SFDBlock, diskBlock);
            setFontColor(10);
            cout << "退出成功，谢谢使用！\n";
            exit(0);
        }
            //退出当前用户
        else if (in1 == "logout") {
            user.userName = "";
            setFontColor(10);
            cout << "退出成功!\n";
            system("cls");
            login(user);
            //init();
            cout << "欢迎使用文件系统！\n" << endl;
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
            //格式化当前用户
        else if (in1 == "format") {
            if (user.userName.empty()) { //用户名为空
                setFontColor(10);
                cout << "请先进行登录，再进行格式化！\n";
                continue;
            }
            setFontColor(12);
            cout << "警告：格式化将删除该用户的所有文件数据。\n" << "继续请输入Y，若想退出，请输入N： ";
            string strtmp;
            while (true) {
                cin >> strtmp;
                if (strtmp == "N" || strtmp == "n")
                    break;
                else if (strtmp != "Y" && strtmp != "y") {

                    setFontColor(12);
                    cout << "输入不合法，请重新输入\n";
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
            cout << "格式化成功！\n";
        }
            //创建文件
        else if (in1 == "create") {
            filename.clear();
            //cin >> filename;
            //cin.sync();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {//根据 flag 的值来判断是否需要清空输入缓冲区

                getchar();
                cin.sync();
            } else flag = 1;
            int cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD); //获取当前目录的索引号 
            if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {
                setFontColor(12);
                cout << "创建失败，您没有在该目录下创建文件的权限" << endl;
                continue;
            }
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
            for(int checki=filename.length()-1;checki>=0;checki--){
                if(filename[checki]=='\\'){
                    break;
                }
                else{
                    filename3 = filename3 + filename[checki];//代码根据文件名中的路径信息提取出目标文件名的倒序形式，存储在 filename3 变量中
                }
            }
            if(filename3 == ""){
                setFontColor(12);
                cout<< "文件名为空，无法创建文件，请重新创建文件！"<<endl;
                continue;
            }
            string filename4="";          //要创建的文件名
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];//通过反转 filename3 的字符顺序，得到要创建的文件名，存储在 filename4 变量中。
            }
            int tmpauth = checkDirAuth(filename4, fileSystem, *cur_SFD, user.userName, iNode);
            if (tmpauth == -2) {
                setFontColor(12);
                cout << "此文件名已存在，创建文件失败！\n";
                continue;
            }
            //cout<<filename.length()<<endl;
            for(int checki=0;checki<=filename.length();checki++){
                if( (filename[checki]=='\\') || (checki==filename.length()) ) {//如果遇到 '\\' 字符或已经遍历到字符串末尾，则表示已经提取到一个目录名
                    if(filename2 == filename4){
                        break;
                    }
                    else{
                        //cout<<filename2<<endl;
                        str += "\\" + filename2;
                        //cout<<str<<endl;
                        int tmpauth = checkDirAuth(filename2, fileSystem, *cur_SFD, user.userName, iNode);//检查该目录名是否已经存在
                        if (tmpauth == -2) {
                            //cout << "已存在的文件名或目录名，创建目录失败！\n";
                            if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                //cout << "操作成功！\n"; //如果目录名已存在，则进入该目录
                                (*staSFD).push(*cur_SFD);
                            }
                        } else if (tmpauth == 0) { 
                            setFontColor(12);
                            cout << "创建失败，您不具有创建该目录权限！\n";
                        } else {
                            if (createDir(filename2, fileSystem, user.userName, iNode, SFDBlock, *cur_SFD)){
                                setFontColor(10);
                                cout << "创建成功！\n";
                                if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                    //cout << "操作成功！\n";
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
                cout << "是否立刻写入内容？\n" << "立刻写入请输入Y，稍后写入请输入N： ";
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
                        cout << "输入不合法，请重新输入\n";
                    }
                }
            }

        }
            //读文件
        else if (in1 == "read") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，读取文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "读取失败，文件未打开或不存在，请打开或创建后重试！\n";
                continue;
            }
            int cur_iNode = sysOFile[user.uOpenFile.SysOFId[index] - 1].iId;
            int usr = checkUser(user.userName) - 1;
            readFile(filename4, *fileSystem, *cur_SFD);
            cout << endl;
            if ((*fileSystem).iNode[cur_iNode].type == 1) {
                setFontColor(12);
                cout << "读取失败，读取的文件为目录文件！\n";
                continue;
            } else if ((*fileSystem).iNode[cur_iNode].auth[usr] == -1) {
                setFontColor(12);
                cout << "读取失败，您不具有读取权限！\n";
                continue;
            } else {
                readFile(filename4, *fileSystem, *cur_SFD);
                cout << endl;
            }
        }    //打开文件
        else if (in1 == "open") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，打开文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
        }    //关闭文件
        else if (in1 == "close") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，关闭文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
            //创建目录
        else if (in1 == "mkdir") {
            filename.clear();
            //cin >> filename;
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，创建文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
            for(int checki=filename3.length()-1;checki>=0;checki--){
                filename4 = filename4 + filename3[checki];
            }
            int tmpauth = checkDirAuth(filename4, fileSystem, *cur_SFD, user.userName, iNode);
            if (tmpauth == -2) {
                setFontColor(12);
                cout << "已存在的文件名或目录名，创建目录失败！\n";
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
                        //cout << "已存在的文件名或目录名，创建目录失败！\n";
                        if (goNextDir(filename2, *fileSystem, cur_SFD)){
                            //setFontColor(6);
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                        }
                    } else if (tmpauth == 0) {
                        setFontColor(12);
                        cout << "创建失败，您不具有创建该目录权限！\n";
                    } else {
                        if (createDir(filename2, fileSystem, user.userName, iNode, SFDBlock, *cur_SFD)){
                            setFontColor(10);
                            cout << "创建成功！\n";
                            if (goNextDir(filename2, *fileSystem, cur_SFD)){
                                //setFontColor(6);
                                //cout << "操作成功！\n";
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
            //删除目录
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
                cout << "删除失败，您不具有删除目录权限！\n";
                continue;
            }
            else {
                string filename2="";
                string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                    cout<< "文件名为空，删除目录失败！"<<endl;
                    continue;
                }
                string filename4="";          //要读的文件名
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
                                //cout << "操作成功！\n";
                                (*staSFD).push(*cur_SFD);
                                filename2 = "";
                            }
                            else{
                                flag_out=0;
                                setFontColor(6);
                                //cout << "操作失败！\n";
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
                    cout << "删除失败，目录名不存在！\n";
                    continue;
                }
                int cur_inode = (*fileSystem).sfd[(*cur_SFD)].sfdVec[pos].id;
                if ((*fileSystem).iNode[cur_inode].type == 0) {       //1表示当前i结点是文件
                    setFontColor(12);
                    //cout << "删除失败，输入为文件名！\n";
                    continue;
                }
                if(flag_out==0){
                    continue;
                }
                if (deleteDir(filename4, fileSystem, *cur_SFD, iNode, SFDBlock, diskBlock, user.userName)) {
                    setFontColor(10);
                    cout << "删除成功！\n";
                }
            }
        }
            //删除文件
        else if (in1 == "delf") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            int index = 0;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，删除文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "删除失败，文件正在被打开，请关闭后重试！\n";
                continue;
            }
            int cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD);
            if (freeFile(filename4, fileSystem, *cur_SFD, user.userName, iNode, diskBlock, SFDBlock)) {
                setFontColor(10);
                cout << "删除文件成功！\n";
            }
            if ((*fileSystem).iNode[cur_inode].type == 1) {
                setFontColor(12);
                //cout << "删除失败，输入为目录！！\n";
                continue;
            }else if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {
                setFontColor(12);
                cout << "删除失败，您没有在该目录下删除文件的权限" << endl;
                continue;
            }

        }
            //进入下一级目录
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
                        //cout << "操作成功！\n";
                        (*staSFD).push(*cur_SFD);
                        filename2 = "";
                    }
                    else{
                        setFontColor(6);
                        //cout << "操作失败！\n";
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
            //写文件
        else if (in1 == "write") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            if (flag) {

                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，写文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "写文件失败，文件未打开或不存在，请打开或创建后重试！\n";
                continue;
            }
            int cur_iNode = sysOFile[user.uOpenFile.SysOFId[index] - 1].iId;
            int usr = checkUser(user.userName) - 1;
            if ((*fileSystem).iNode[cur_iNode].type == 1) {
                setFontColor(12);
                cout << "写文件失败，待写的文件为目录文件！\n";
                continue;
            } else if ((*fileSystem).iNode[cur_iNode].auth[usr] == -1 ||
                       (*fileSystem).iNode[cur_iNode].auth[usr] == 0) {
                setFontColor(12);
                cout << "写文件失败，您不具有写该文件的权限！\n";
                continue;
            } else {
                writeFile(filename4, fileSystem, *cur_SFD, diskBlock);
            }
        }
            //复制文件
        else if (in1 == "copy") {
            filename.clear();
            cin_name(filename, *fileSystem, *cur_SFD, flag);
            *copy_flag = 1;//copy
            if (flag) {
                getchar();
                cin.sync();
            } else flag = 1;
            string filename2="";
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，复制文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "复制成功\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "复制失败\n";
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
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，写文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "剪切成功\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "剪切失败\n";
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
            string filename3="";//将路径过滤掉，得到目标文件名的倒序名字
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
                cout<< "文件名为空，写文件失败！"<<endl;
                continue;
            }
            string filename4="";          //要读的文件名
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
                            //cout << "操作成功！\n";
                            (*staSFD).push(*cur_SFD);
                            filename2 = "";
                        }
                        else{
                            flag_out=0;
                            setFontColor(6);
                            //cout << "操作失败！\n";
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
                cout << "已准备好链接\n";
            } else {
                *copy_flag = 0;
                setFontColor(12);
                cout << "链接失败\n";
            }
        }
            //粘贴文件
        else if (in1 == "paste") {
            if (pasteContext(*copy_flag, *copySFD, *cur_SFD, fileSystem, user.userName, iNode, diskBlock, SFDBlock))
                cout << "粘贴成功\n";
        }
            //返回上级目录
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
            //返回根目录
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
            int i, cur_inode = getInodeNum(iNode, *fileSystem, *cur_SFD);    //获得当前目录的i节点号
            if ((*fileSystem).iNode[cur_inode].id != checkUser(user.userName)) {    //判断登录用户和i节点所属用户是否相同
                setFontColor(12);
                cout << "更名失败，您没有在该目录下更名的权限" << endl;
                continue;
            }
            else {
                for (i = 0; i < (*fileSystem).sfd[*cur_SFD].sfdVec.size(); i++) {
                    if ((*fileSystem).sfd[*cur_SFD].sfdVec[i].name == filename) {    //遍历文件系统目录块中每个目录项的文件名，找到则退出循环
                        break;
                    }
                }
                if (i != (*fileSystem).sfd[*cur_SFD].sfdVec.size()) {    //找到了所要更改的文件名
                    (*fileSystem).sfd[*cur_SFD].sfdVec[i].name = rname;    //重命名
                    setFontColor(10);
                    cout << "更名成功\n";
                }
                else {
                    setFontColor(12);
                    cout << "未找到指定文件或目录名\n";
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
            cout << "\n文件名\t\t路径" << endl;
            setFontColor(11);
            if (str.size() < 12)find_filedir(str.substr(11), filename, *fileSystem, *cur_SFD);
            else find_filedir("\\" + str.substr(12), filename, *fileSystem, *cur_SFD);
        }
        else if (in1 == "print") {
            setFontColor(14);
            cout << "请输入查看内容选项\n";
            cout << endl;
            cout << "1:位示图信息             2:磁盘块i结点信息\n";
            cout << "\n";
            cout << "3:详细信息               4：空闲磁盘块信息\n";
            cout << "\n";
            string in2;
            cin >> in2;
            if (in2 == "1") {
                system("cls");
                setFontColor(14);
                cout << "索引结点位矢图\n" << endl;
                for (int i = 0; i < (*fileSystem).superBlock.i_node; i++) {
                    if (iNode[i] == 0) setFontColor(12);
                    else setFontColor(10);
                    cout << " " << iNode[i] << " ";
                    if ((i + 1) % 16 == 0) cout << endl;
                }
                cout << endl << endl << endl;
                setFontColor(14);
                cout << "磁盘块位矢图\n" << endl;
                for (int i = 0; i < (*fileSystem).superBlock.disk; i++) {
                    if (diskBlock[i] == 0) setFontColor(12);
                    else setFontColor(10);
                    cout << " " << diskBlock[i] << " ";
                    if ((i + 1) % 16 == 0) cout << endl;
                }
                cout << endl << endl << endl;
                setFontColor(14);
                cout << "sfd位矢图\n" << endl;
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
            else { cout << "输入选项有误\n"; }


            }
        else {
                setFontColor(12);
                //cout << fileSystem.superBlock.freeDisk << "  " << fileSystem.superBlock.freei_node << "  " << fileSystem.superBlock.free_SFD << endl;
                cout << "无此命令，无此功能；\n更多功能，敬请期待！" << endl;
                }
    }
}

/**
 * 设置字体颜色
 * @param color 10:绿色  14:黄色   12:红色
 */
void setFontColor(int color) {
    if (color == 14) color++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);  //标准的输出设备的句柄，获得输出的屏幕缓冲区的句柄。
}


/**
 * @brief 用来检测命令是否存在以及指令的种类
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
 * 判断文件是否打开
 * @param user
 * @param sysOFile
 * @param filename
 * @param index
 * @return
 */
bool hasOpen(User& user, SysOpenFile* sysOFile, string filename, int& index) {
    for (int i = 0; i < NOFILE; i++) {  //NOFILE:每个用户最多可打开20个文件，即用户打开文件最大次数
        if (user.uOpenFile.SysOFId[i] != -1) {  //系统中其他进程已打开该文件
            //cout << sysOFile[user.uOpenFile.SysOFId[i] - 1].fileName << endl;
            if (sysOFile[user.uOpenFile.SysOFId[i] - 1].fileName == filename) {
                index = i;    //如果想打开的文件与在用户文件打开文件表中指向系统打开文件表的文件名相同则返回该文件描述符表示该进程已打开
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
void printFreeDiskGroup() {  //输出成组链接前两个组长块
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

void print(FileSystem fileSystem, int* iNode, int* diskBlock, int* SFDBlock) {  //输出i节点，磁盘块，目录块全部信息
    cout << "第几个i节点\t" << "所属用户\t类型\t对应目录id\t权限\t  所在的磁盘/目录块" << endl;
    setFontColor(10);  //绿色
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

                cout << fileSystem.iNode[i].diskBlockId << endl;    //文件则打印出该文件所占磁盘块的id号的索引块
            }
            else {
                cout << fileSystem.iNode[i].sfd_id << endl;    //目录则打印出i结点对应的目录id
            }
            /*
            if (fileSystem.iNode[i].type == 1){
            int number = fileSystem.iNode[i].sfd_id;
            if (fileSystem.sfd[number].sfdVec.size() != 0)
            cout << fileSystem.sfd[number].sfdVec[0].name;
            else cout << "为空！";
            }*/
        }
    }
    setFontColor(14);
    cout << endl;
    cout << "第几个磁盘块\t" << "长度\t" << "\t内容" << endl;
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
    cout << "第几个目录块\t" << "长度\t" << "内容（对应i节点编号）" << endl;
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

void FreeDiskGroup(FileSystem fileSystem, int* diskBlock) {  //输出成组链接组长块信息
    for (int i = 0; i < 512; i++) {
        if (fileSystem.diskBlock[i].file.size() > 0 && diskBlock[i] == 1) {
            setFontColor(10);
            cout << "组长块是 : ";

            cout << i << " 内容是: ";
            setFontColor(14);
            cout << fileSystem.diskBlock[i].file << endl;

        }
    }
}

void printDiskBitmap(FileSystem fileSystem, int iNode[]) {  //输出磁盘块位示图
    vector<vector<diskBlock_iNode>> fileBlocks;
    for (int i = 0, k = 1; i < 128; i++) {
        if (iNode[i] == 0) {
            if (fileSystem.iNode[i].type == 0) {    //文件
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

void printFreeDiskGroup1(FileSystem fileSystem) {  //显示成组链接前两个组长块中内容
    int group[12] = { 0 };
    for (int ii = 0; ii < BLOCK_NUM + 1; ii++) {
        group[ii] = fileSystem.superBlock.freeDiskSta[ii];//group[0]-group[5]显示的是成组链接空闲磁盘块栈中内容
    }
    if (fileSystem.superBlock.freeDiskSta[1] != DISK_NUM) { //空闲块未分配完毕
        int flag = 0;
        string file = fileSystem.diskBlock[fileSystem.superBlock.freeDiskSta[1]].file;  //空闲磁盘块栈中次栈顶的磁盘块内容赋给file（次栈顶磁盘块是下一组组长块）
        int tmp = 0;
        for (int ii = BLOCK_NUM + 1, jj = 0; ii < 2 * BLOCK_NUM + 2, jj < file.size(); jj++) {
            if (file[jj] != ' ') {
                flag = 1;
                tmp = tmp * 10 + file[jj] - '0';
            }
            else if (flag == 1 && file[jj] == ' ') {
                group[ii] = tmp;  //将file中的内容分别赋给group[6]-[11]
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