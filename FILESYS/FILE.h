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
#define INODE_NUM 128    //i�ڵ����
#define DISK_NUM 512     //���̿���
#define SFD_NUM 512      //Ŀ¼����
#define DISK_LEN 512     //���̿��С
#define BLOCK_NUM 5      //������

#define BLOCKSIZ  512  //ÿ���С
#define SYSOPENFILE 40  //ϵͳ���ļ����������
#define DIRNUM  128  //ÿ��Ŀ¼�����������Ŀ¼�������ļ�����
#define DIRSIZ  14  //ÿ��Ŀ¼�����ֲ�����ռ�ֽ��������i�ڵ��2���ֽ�
#define PWDSIZ   12  //������
#define PWDNUM   32  //������32�������¼
#define NOFILE  20  //ÿ���û����ɴ�20���ļ������û����ļ�������
#define NADDR 13  //ÿ��i�ڵ����ָ��13�飬addr[0]~addr[12]
#define NHINO  128  //��128��Hash�����ṩ����i�ڵ㣨����Ϊ2���ݣ�
#define USERNUM  10  //�������10���û���¼
#define DINODESIZ  32 //ÿ������i�ڵ���ռ�ֽ�
#define DINODEBLK  32  //���д���i�ڵ㹲ռ32�������
#define FILEBLK  512  //����512��Ŀ¼�ļ������
#define NICFREE  50  //�������п��п������������
#define NICINOD  50  //�������п��нڵ��������
#define DINODESTART 2*BLOCKSIZ  //i�ڵ���ʼ��ַ
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //Ŀ¼���ļ�����ʼ��ַ
#define com_num  24 //��������

//ϵͳ���ļ���
struct SysOpenFile {
    int id;       //�ļ���ʶ
    string fileName; //�ļ���
    int count;    //���ʼ���
    int iId;         //�ļ���Ӧ��i����id��
};

//�û����ļ���
struct UserOpenFile {
    int userId;   //�û�id
    int SysOFId[NOFILE];  //ָ��ϵͳ���ļ�����ļ�
};

struct User {
    string userName; //�û���
    int userType;    //�û����� 0:����Ա 1:��ͨ�û�
    int userId;      //�û�id
   // int groupId;     //��id
    UserOpenFile uOpenFile; //�û����ļ���
};
struct SingleSFD {	//����Ŀ¼��
    string name;    //�ļ���
    int id;         //�ļ���Ӧ��i����id��
    int delink;        //���ӣ�0-���ӣ�1-������
};

struct SFD {						//Ŀ¼�ṹ
    int sfdNum;                 //��̬����Ĵ�С
    vector<SingleSFD> sfdVec;   //Ŀ¼�µ�sfd����
};

struct DiskBlock {	//���̿�ṹ
    string file;	//�ļ�����
    int strNum;		//�ļ�����, 0-δռ�ã�-1-�鳤��
};

struct INode {			//i���ṹ
    int id;				//i����������û�
    int type;			//�ļ����ͣ�0-�ļ���1-Ŀ¼
    int sfd_id;			//i����Ӧ��Ŀ¼id
    int filelen;		//�ļ�����
    int auth[8];		//8��user�ķ���Ȩ��
    int diskBlockNum;   //�ļ�ռ�ô��̿����
    int diskBlockId;    //��ռ���̿��id�ŵ�������
    int qcount;         //�ļ���������
};

struct SuperBlock {		 //������ṹ
    int i_node;          //i�������
    int freei_node;      //����i�������
    vector<int> freeiid; //����i���id����

    int sfd;             //Ŀ¼��Ŀ
    int free_SFD;        //����Ŀ¼��
    vector<int> freeSFD; //����Ŀ¼�±�����

    int disk;			 //���̿��ܿ���
    int freeDisk;        //���д��̿����
    int freeDiskSta[BLOCK_NUM + 1]; //�������ӿ��д��̿�ջ
};

struct FileSystem {			 //�ļ�ϵͳ�ṹ
    int boot;                //������
    SuperBlock superBlock;   //������
    INode iNode[INODE_NUM];        //i���
    DiskBlock diskBlock[DISK_NUM]; //���̿�
    SFD sfd[SFD_NUM];              //Ŀ¼��
};

//**************************��ʼ��ģ��***************************

void initSuperBlock(FileSystem* fileSystem, int* iNode,
    int* SFDBlock, int* diskBlock);													//��ʼ��������
void initINode(FileSystem* fileSystem, int* iNode);                                 //��ʼ��i���
void initDiskBlock(int* diskBlock, FileSystem* fileSystem);                         //��ʼ�����̿�
void initSFD(FileSystem* fileSystem, stack<int>* staSFD, int* SFDBlock);            //��ʼ��SFD
void initFileSystem(int* iNode, int* diskBlock, int* SFDBlock,
    FileSystem* fileSystem, stack<int>* staSFD);									//��ʼ���ļ�ϵͳ
void initOpenFileList(SysOpenFile* sysOpenFile); //��ʼ��ϵͳ���ļ��б�
//**************************�û�ģ��*****************************

void login(User& user);															//��¼�û���
void logout(User& user, FileSystem fileSystem,
    int* iNode, int* SFDBlock, int* diskBlock);										//�˳�
int checkUser(string user);															//�жϴ�ʱ�û�
int getInodeNum(int* iNode, FileSystem fileSystem, int cur_SFD);					//��õ�ǰĿ¼��i����
int checkFileAuth(const string& fileName, FileSystem* fileSystem,
    int cur_SFD, string user);														//��鵱ǰ�û��Ķ�дȨ��
int checkDirAuth(const string& fileName, FileSystem* fileSystem,
    int cur_SFD, string user, int* iNode);											//��鵱ǰ�û���Ŀ¼�Ķ�дȨ��

//**************************����ģ��*****************************

void help();																	//��ʾ����
void display(User& user, int* cur_SFD, stack<int>* staSFD, SysOpenFile* sysOFile,
    FileSystem* fileSystem, int* copy_flag, int* iNode,
    int* diskBlock, int* SFDBlock, SingleSFD* copySFD);								//����������������ʵ�ִ󲿷������������
void setFontColor(int color);															//����������ɫ
int checkIn(const string& in);																//������������Ƿ�����Լ�ָ�������
void printFreeDiskGroup();
void print(FileSystem  fileSystem, int* iNode,
    int* diskBlock, int* SFDBlock);
void FreeDiskGroup(FileSystem  fileSystem, int* diskBlock);
void printDiskBitmap(FileSystem fileSystem, int iNode[]);
void printFreeDiskGroup1(FileSystem fileSystem);
bool hasOpen(User& user, SysOpenFile* sysOFile, string filename, int& index);
//**************************�Զ���ȫģ��*****************************
void cin_name(string& name, FileSystem fileSystem, int cur_SFD, int& flag);					//�ļ�/Ŀ¼������
void cin_command(string& in, int& flag);														//ָ������

//**************************���д��̿�����ͷ�ģ��*****************************
void writeABlock(int r, FileSystem* fileSystem);									//��װ����ջ����д��һ���ض����̿�
void readABlock(int r, FileSystem* fileSystem);										//��һ��д�ſ��д��̿�õĴ��̿�����д��ջ
void freeABlock(int BlockNo, int* diskBlock,
    FileSystem* fileSystem, int* SFDBlock);											//�ڳ��������л���һ�����д��̿�
int allocateOneBlock(FileSystem* fileSystem, int* diskBlock);						//�ڳ��������з���һ�����д��̿�


//**************************�ļ��Ĵ�����ɾ��ģ��*****************************
int createFirstIndexB(FileSystem* fileSystem, int* diskBlock);						//�����ļ��ĵ�һ��������
int createiNode(FileSystem* fileSystem, int* iNode,
    string user, int* diskBlock, int* SFDBlock);									//Ϊ�´������ļ�����һ��i���
int checkExitsfd(string name, FileSystem fileSystem, int cur_SFD);					//��ѯ��ǰĿ¼��һ�̶������ļ��±�
int createFile(string name, FileSystem* fileSystem, int cur_SFD,
    int* iNode, string user, int* diskBlock, int* SFDBlock);						//�����ļ�
int freeFile(string name, FileSystem* fileSystem, int cur_SFD,
    string user, int* iNode, int* diskBlock, int* SFDBlock);						//ɾ��ָ�����ֵ��ļ�
void deleteINode(int pos, FileSystem* fileSystem, int cur_SFD,
    int* iNode, int* diskBlock, int* SFDBlock);										//ɾ����ɾ���ļ���Ӧ��i��㼰��ָ��Ĵ��̿�
void findSinglesfd(int inodeNo, FileSystem* fileSystem, int cur_SFD);				//����ɾ�����ɾ���ļ�������ļ�Ŀ¼

//**************************�ļ��Ĵ���ر�ģ��*****************************
void openFile(string name, FileSystem fileSystem, int cur_SFD, User& user, SysOpenFile* sysOpenFile);  //���ļ�
void closeFile(string name, FileSystem fileSystem, int cur_SFD, User& user, SysOpenFile* sysOpenFile); //�ر��ļ�
//**************************�ļ��Ķ�дģ��*****************************
void writeiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem);					//�������е���������д�ص���Ӧ���������У������ļ���
void secondWriteiaddr(int BlockNo, int* iaddr, FileSystem* fileSystem);             //д��������
void outputBlock(int blockNO, FileSystem fileSystem);								//����ļ����̿�����
void readFile(string name, FileSystem fileSystem, int cur_SFD);						//���ļ����ݺ���
int writeIndexBlock(int indexnum, int BlockNo,
    FileSystem* fileSystem, int* diskBlock);										//�ļ����ݵ�д��
int getCur_blockNo(int inodeNo, FileSystem fileSystem);								//���ص�ǰ�ļ�i�ڵ㣬��ռ�õ������̿�
int writeFile(string name, FileSystem* fileSystem, int cur_SFD, int* diskBlock);    //дָ���ļ������ļ�
void writeContent(string& content);
int writeDisk(int pos, FileSystem* fileSystem, int cur_SFD, int* diskBlock, string content);
int* getIaddr(int indexnum, FileSystem fileSystem);									//�õ���ɾ���ļ����������еĴ��̿������
//**************************Ŀ¼�Ĵ���ɾ��ģ��*****************************
void showSFD(FileSystem fileSystem, int cur_SFD);									//չʾSFD
void createInitINode(int useINode, int type, int filelen,
    FileSystem* fileSystem, string user, int* iNode, int* SFDBlock);				//Ϊ�����ļ���Ŀ¼��ʼ��i���
int createDir(string filename, FileSystem* fileSystem,
    string user, int* iNode, int* SFDBlock, int cur_SFD);							//����һ��Ŀ¼
void deleteINodeOne(int useINode, int cur_SFD,
    FileSystem* fileSystem, int* iNode, int* SFDBlock,
    int* diskBlock, string user);													//ɾ��һ��i���
int deleteDir(string name, FileSystem* fileSystem, int cur_SFD,
    int* iNode, int* SFDBlock, int* diskBlock, string user);						//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
int goNextDir(string filename, FileSystem fileSystem, int* cur_SFD);				//������һ��Ŀ¼

//**************************����ճ��ģ��*****************************
int copyContext(string filename, FileSystem fileSystem,
    int cur_SFD, SingleSFD* copySFD, int* copy_flag);								//����ָ�����ֵ�Ŀ¼���ļ�
int cutContext(string filename, SingleSFD* copySFD,
    FileSystem* fileSystem, int cur_SFD);											//����ָ�����ֵ�Ŀ¼���ļ�
int pasteContext(int copy_flag, SingleSFD copySFD, int cur_SFD,
    FileSystem* fileSystem, string user, int* iNode,
    int* diskBlock, int* SFDBlock);													//ճ��ճ�����ϵ����ݵ���ǰĿ¼��
int blocksNeeded(FileSystem* fileSystem, int* iNode,
    int* diskBlock, SingleSFD copySFD);
//**************************���Һ�������ģ��************************
void find_filedir(string cur_path, string name,
    FileSystem fileSystem, int cur_SFD);											//�����ļ�
//**************************��ʽ��ģ��*****************************
void formatUser(FileSystem* fileSystem, int cur_SFD, int* iNode,
    int* SFDBlock, int* diskBlock, string user);									//�û��ĸ�ʽ��

//**************************�˳�ģ��*****************************
void exitSFD(int* SFDBlock, FileSystem fileSystem);									//�˳�ǰ����SFD����
void exitDiskBlock(int* diskBlock, FileSystem fileSystem);							//�˳�ǰ������̿�����
void exitINode(int* iNode, FileSystem fileSystem);									//�˳�ǰ����i�ڵ�����
void exitSuperBlock(FileSystem fileSystem, int* diskBlock);							//�˳�ǰ���泬��������
void exitSystem(FileSystem fileSystem, int* iNode, int* SFDBlock, int* diskBlock);  //�˳�ϵͳ

#endif //FILE_H
