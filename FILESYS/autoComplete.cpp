#include "FILE.h"

static string com[com_num] = { "link", "cd", "create", "rname",
                        "mkdir", "find","write", "read",
                        "deld", "delf","copy", "cut",
                        "paste", "cd..", "cd/", "ls",
                        "clear", "format", "logout", "exit",
                        "help", "print", "open" ,"close" };
/**
 *
 * @param name
 * @param fileSystem
 * @param cur_SFD
 */
void cin_name(string& name, FileSystem fileSystem, int cur_SFD, int& flag) {
    char c;
c1:     while ((c = getch()) == ' ' && name.size() == 0)putchar(' ');     //��ȥǰ������Ŀո�
    while (c == 13) goto c1;    //���һֱ������ǻس��������21.22֮��ѭ��ִ��ֱ������Ĳ��ǻس���
    while (c > 32) {    //����������ķǿ����ַ�����name
        name += c;
        cout << c;
        c = getch();
    }
    if (c == '\t') {    //�����������tab������ļ���Ŀ¼����ȫ
        int pos, num = 0;
        for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i) {
            if (fileSystem.sfd[cur_SFD].sfdVec[i].name.find(name) != string::npos) {//�����ļ�ϵͳĿ¼����ÿ��Ŀ¼����ļ��������Ƿ���ƥ���name�Ӵ�
                pos = i;
                num++;
            }
        }
        if (num == 1) {     //������ϵ�ǰ�����ָ��ֻ��һ���򸳸�name���������
            for (int i = 0; i < name.size(); ++i)putchar('\b');    //�����ӵ�ǰλ�������ƶ�һ���ַ������ԭ�������name�Ա㽫�ҵ���ƥ���ָ���name
            cout << fileSystem.sfd[cur_SFD].sfdVec[pos].name;
            name = fileSystem.sfd[cur_SFD].sfdVec[pos].name;
            return;
        }
        else cin_name(name, fileSystem, cur_SFD, flag);    //���û���ҵ�ƥ����ļ�����Ŀ¼�������ҵ��������ȷ����ƥ�������������
    }
    else if (c == 8) {     //������������˸���ɾ����һ���ַ�
        if (name.size() > 0) {
            name.erase(name.size() - 1);    //�����������ɾ�����һ���ַ�
            fflush(stdout); putchar('\b'); fflush(stdout);     //������������е������������Ļ�ϲ�������������
            putchar(' ');
            fflush(stdout);	putchar('\b'); fflush(stdout);
        }
        cin_name(name, fileSystem, cur_SFD, flag);    //��������
    }
    else {
        if (c == 13) {    //��������Ļس������������
            cout << endl;
            flag = 0;
        }
        else cout << c;
        return;
    }
}

/**
 * ָ������
 * @param in
 */
void cin_command(string& in, int& flag) {
    char c;
    while ((c = getch()) == ' ' && in.size() == 0)putchar(' ');    //��ȥǰ������Ŀո�

    while (c > 32) {
        in += c;    //����������ķǿ����ַ�����in
        cout << c;
        c = getch();
    }
    if (c == '\t') {   //�����������tab�����ָ�ȫ
        int pos, num = 0;
        for (int i = 0; i < com_num; ++i) {
            if (com[i].find(in) != string::npos) {   //�����ַ���com[i]���Ƿ�����Ӵ�in���Ҳ����򷵻�string::npos����������ҵ����ϵ�ǰ�����ָ��
                num++;
                pos = i;
            }
        }
        if (num == 1) {    //������ϵ�ǰ�����ָ��ֻ��һ���򸳸�in���������
            for (int i = 0; i < in.size(); ++i)putchar('\b');    //���ԭ�������in�Ա㽫�ҵ���ƥ���ָ���in
            cout << com[pos];
            in = com[pos];
            return;
        }
        else cin_command(in, flag);    //���û���ҵ����ʵ�ָ�����������
    }
    else if (c == 8) {      //������������˸���ɾ����һ���ַ�
        if (in.size() > 0) {
            in.erase(in.size() - 1);    //ɾ�����һ���ַ�
            fflush(stdout); putchar('\b'); fflush(stdout);    //������������е������������Ļ�ϲ�������������
            putchar(' ');
            fflush(stdout);	putchar('\b'); fflush(stdout);
        }
        cin_command(in, flag);    //��������
    }
    else {
        if (c == 13) {       //��������Ļس������������
            cout << endl;
            flag = 0;
        }
        else cout << c;
        return;
    }
}