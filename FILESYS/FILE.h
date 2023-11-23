//
// Created by SGNY on 2022/5/23.
//

#ifndef FILE_H
#define FILE_H

#pragma warning(disable:4996)

// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2017 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

 // 17.4.1.2 Headers

 // C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif



#include <conio.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;
#define INODE_NUM 128    //i节点个数
#define DISK_NUM 512     //磁盘块数
#define SFD_NUM 512      //目录个数
#define DISK_LEN 512     //磁盘块大小
#define BLOCK_NUM 5      //组容量

#define BLOCKSIZ  512  //每块大小
#define SYSOPENFILE 40  //系统打开文件表最大项数
#define DIRNUM  128  //每个目录所包含的最大目录项数（文件数）
#define DIRSIZ  14  //每个目录项名字部分所占字节数，另加i节点号2个字节
#define PWDSIZ   12  //口令字
#define PWDNUM   32  //最多可设32个口令登录
#define NOFILE  20  //每个用户最多可打开20个文件，即用户打开文件最大次数
#define NADDR 13  //每个i节点最多指向13块，addr[0]~addr[12]
#define NHINO  128  //共128个Hash链表，提供索引i节点（必须为2的幂）
#define USERNUM  10  //最多允许10个用户登录
#define DINODESIZ  32 //每个磁盘i节点所占字节
#define DINODEBLK  32  //所有磁盘i节点共占32个物理块
#define FILEBLK  512  //共有512个目录文件物理块
#define NICFREE  50  //超级块中空闲块数组的最大块数
#define NICINOD  50  //超级块中空闲节点的最大块数
#define DINODESTART 2*BLOCKSIZ  //i节点起始地址
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //目录、文件区起始地址
#define com_num  24 //命令数量

//系统打开文件表
struct SysOpenFile {
    int id;       //文件标识
    string fileName; //文件名
    int count;    //访问计数
    int iId;         //文件对应的i结点的id号
};

//用户打开文件表
struct UserOpenFile {
    int userId;   //用户id
    int SysOFId[NOFILE];  //指向系统打开文件表的文件
};

struct User {
    string userName; //用户名
    int userType;    //用户类型 0:管理员 1:普通用户
    int userId;      //用户id
   // int groupId;     //组id
    UserOpenFile uOpenFile; //用户打开文件表
};
struct SingleSFD {	//单个目录项
    string name;    //文件名
    int id;         //文件对应的i结点的id号
    int delink;        //链接，0-链接，1-被链接
};

struct SFD {						//目录结构
    int sfdNum;                 //动态数组的大小
    vector<SingleSFD> sfdVec;   //目录下的sfd数组
};

struct DiskBlock {	//磁盘块结构
    string file;	//文件内容
    int strNum;		//文件长度, 0-未占用，-1-组长块
};

struct INode {			//i结点结构
    int id;				//i结点所属的用户
    int type;			//文件类型，0-文件，1-目录
    int sfd_id;			//i结点对应的目录id
    int filelen;		//文件长度
    int auth[8];		//8个user的访问权限
    int diskBlockNum;   //文件占用磁盘块个数
    int diskBlockId;    //所占磁盘块的id号的索引块
    int qcount;         //文件的引用数
};

struct SuperBlock {		 //超级块结构
    int i_node;          //i结点总数
    int freei_node;      //空闲i结点总数
    vector<int> freeiid; //空闲i结点id数组

    int sfd;             //目录数目
    int free_SFD;        //空闲目录数
    vector<int> freeSFD; //空闲目录下表数组

    int disk;			 //磁盘块总块数
    int freeDisk;        //空闲磁盘块块数
    int freeDiskSta[BLOCK_NUM + 1]; //成组链接空闲磁盘块栈
};

struct FileSystem {			 //文件系统结构
    int boot;                //引导区
    SuperBlock superBlock;   //超级块
    INode iNode[INODE_NUM];        //i结点
    DiskBlock diskBlock[DISK_NUM]; //磁盘块
    SFD sfd[SFD_NUM];              //目录块
};

//**************************初始化模块***************************

void initSuperBlock(FileSystem* fileSystem, int* iNode,
    int* SFDBlock, int* diskBlock);													//初始化超级块
void initINode(FileSystem* fileSystem, int* iNode);                                 //初始化i结点
void initDiskBlock(int* diskBlock, FileSystem* fileSystem);                         //初始化磁盘块
void initSFD(FileSystem* fileSystem, stack<int>* staSFD, int* SFDBlock);            //初始化SFD
void initFileSystem(int* iNode, int* diskBlock, int* SFDBlock,
    FileSystem* fileSystem, stack<int>* staSFD);									//初始化文件系统
void initOpenFileList(SysOpenFile* sysOpenFile); //初始化系统打开文件列表
//**************************用户模块*****************************

void login(User& user);															//登录用户名
void logout(User& user, FileSystem fileSystem,
    int* iNode, int* SFDBlock, int* diskBlock);										//退出
int checkUser(string user);															//判断此时用户
int getInodeNum(int* iNode, FileSystem fileSystem, int cur_SFD);					//获得当前目录的i结点号
int checkFileAuth(const string& fileName, FileSystem* fileSystem,
    int cur_SFD, string user);														//检查当前用户的读写权限
int checkDirAuth(const string& fileName, FileSystem* fileSystem,
    int cur_SFD, string user, int* iNode);											//检查当前用户对目录的读写权限

//**************************界面模块*****************************

void help();																	//显示帮助
void display(User& user, int* cur_SFD, stack<int>* staSFD, SysOpenFile* sysOFile,
    FileSystem* fileSystem, int* copy_flag, int* iNode,
    int* diskBlock, int* SFDBlock, SingleSFD* copySFD);								//界面主函数，用来实现大部分输入输出功能
void setFontColor(int color);															//设置字体颜色
int checkIn(const string& in);																//用来检测命令是否存在以及指令的种类
void printFreeDiskGroup();
void print(FileSystem  fileSystem, int* iNode,
    int* diskBlock, int* SFDBlock);
void FreeDiskGroup(FileSystem  fileSystem, int* diskBlock);
void printDiskBitmap(FileSystem fileSystem, int iNode[]);
void printFreeDiskGroup1(FileSystem fileSystem);
bool hasOpen(User& user, SysOpenFile* sysOFile, string filename, int& index);
//**************************自动补全模块*****************************
void cin_name(string& name, FileSystem fileSystem, int cur_SFD, int& flag);					//文件/目录名输入
void cin_command(string& in, int& flag);														//指令输入

//**************************空闲磁盘块分配释放模块*****************************
void writeABlock(int r, FileSystem* fileSystem);									//将装满的栈内容写入一个特定磁盘块
void readABlock(int r, FileSystem* fileSystem);										//将一个写着空闲磁盘块好的磁盘块内容写入栈
void freeABlock(int BlockNo, int* diskBlock,
    FileSystem* fileSystem, int* SFDBlock);											//在成组链接中回收一个空闲磁盘块
int allocateOneBlock(FileSystem* fileSystem, int* diskBlock);						//在成组链接中分配一个空闲磁盘块


//**************************文件的创建与删除模块*****************************
int createFirstIndexB(FileSystem* fileSystem, int* diskBlock);						//创建文件的第一个索引块
int createiNode(FileSystem* fileSystem, int* iNode,
    string user, int* diskBlock, int* SFDBlock);									//为新创建的文件分配一个i结点
int checkExitsfd(string name, FileSystem fileSystem, int cur_SFD);					//查询当前目录下一固定名的文件下标
int createFile(string name, FileSystem* fileSystem, int cur_SFD,
    int* iNode, string user, int* diskBlock, int* SFDBlock);						//创建文件
int freeFile(string name, FileSystem* fileSystem, int cur_SFD,
    string user, int* iNode, int* diskBlock, int* SFDBlock);						//删除指定名字的文件
void deleteINode(int pos, FileSystem* fileSystem, int cur_SFD,
    int* iNode, int* diskBlock, int* SFDBlock);										//删除待删除文件对应的i结点及其指向的磁盘块
void findSinglesfd(int inodeNo, FileSystem* fileSystem, int cur_SFD);				//遍历删除与待删除文件共享的文件目录

//**************************文件的打开与关闭模块*****************************
void openFile(string name, FileSystem fileSystem, int cur_SFD, User& user, SysOpenFile* sysOpenFile);  //打开文件
void closeFile(string name, FileSystem fileSystem, int cur_SFD, User& user, SysOpenFile* sysOpenFile); //关闭文件
//**************************文件的读写模块*****************************
void writeiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem);					//将数组中的索引内容写回到相应的索引块中，磁盘文件中
void secondWriteiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem);             //写二级索引
void outputBlock(int blockNO, FileSystem fileSystem);								//输出文件磁盘块内容
void readFile(string name, FileSystem fileSystem, int cur_SFD);						//读文件内容函数
int writeIndexBlock(int indexnum, int BlockNo,
    FileSystem* fileSystem, int* diskBlock);										//文件内容的写入
int getCur_blockNo(int inodeNo, FileSystem fileSystem);								//返回当前文件i节点，所占用的最后磁盘块
int writeFile(string name, FileSystem* fileSystem, int cur_SFD, int* diskBlock);    //写指定文件名的文件
void writeContent(string& content);
int writeDisk(int pos, FileSystem* fileSystem, int cur_SFD, int* diskBlock, string content);
int* getIaddr(int indexnum, FileSystem fileSystem);									//得到待删除文件的索引块中的磁盘块号数组
//**************************目录的创建删除模块*****************************
void showSFD(FileSystem fileSystem, int cur_SFD);									//展示SFD
void createInitINode(int useINode, int type, int filelen,
    FileSystem* fileSystem, string user, int* iNode, int* SFDBlock);				//为创建文件或目录初始化i结点
int createDir(string filename, FileSystem* fileSystem,
    string user, int* iNode, int* SFDBlock, int cur_SFD);							//创建一个目录
void deleteINodeOne(int useINode, int cur_SFD,
    FileSystem* fileSystem, int* iNode, int* SFDBlock,
    int* diskBlock, string user);													//删除一个i结点
int deleteDir(string name, FileSystem* fileSystem, int cur_SFD,
    int* iNode, int* SFDBlock, int* diskBlock, string user);						//级联删除一个目录及其子目录和子文件
int goNextDir(string filename, FileSystem fileSystem, int* cur_SFD);				//进入下一级目录

//**************************复制粘贴模块*****************************
int copyContext(string filename, FileSystem fileSystem,
    int cur_SFD, SingleSFD* copySFD, int* copy_flag);								//复制指定名字的目录或文件
int cutContext(string filename, SingleSFD* copySFD,
    FileSystem* fileSystem, int cur_SFD);											//剪切指定名字的目录或文件
int pasteContext(int copy_flag, SingleSFD copySFD, int cur_SFD,
    FileSystem* fileSystem, string user, int* iNode,
    int* diskBlock, int* SFDBlock);													//粘贴粘贴板上的内容到当前目录下
int blocksNeeded(FileSystem* fileSystem, int* iNode,
    int* diskBlock, SingleSFD copySFD);
//**************************查找和重命名模块************************
void find_filedir(string cur_path, string name,
    FileSystem fileSystem, int cur_SFD);											//查找文件
//**************************格式化模块*****************************
void formatUser(FileSystem* fileSystem, int cur_SFD, int* iNode,
    int* SFDBlock, int* diskBlock, string user);									//用户的格式化

//**************************退出模块*****************************
void exitSFD(int* SFDBlock, FileSystem fileSystem);									//退出前保存SFD内容
void exitDiskBlock(int* diskBlock, FileSystem fileSystem);							//退出前保存磁盘块内容
void exitINode(int* iNode, FileSystem fileSystem);									//退出前保存i节点内容
void exitSuperBlock(FileSystem fileSystem, int* diskBlock);							//退出前保存超级块内容
void exitSystem(FileSystem fileSystem, int* iNode, int* SFDBlock, int* diskBlock);  //退出系统

#endif //FILE_H
