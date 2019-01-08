#include<string>
#include<iostream>
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#pragma comment(lib, "shell32.lib")
using namespace std;
/* 通过外壳函数 复制文件或文件夹 */
bool copyFile_bySHFileOperation(const char *pFrom, const char *pTo)
{
    SHFILEOPSTRUCT FileOp={0};
    FileOp.fFlags = FOF_NOCONFIRMATION| //不出现确认对话框
    FOF_NOCONFIRMMKDIR ; //需要时直接创建一个文件夹,不需用户确定
    FileOp.pFrom = pFrom;
    FileOp.pTo = pTo;
    FileOp.wFunc = FO_COPY;
    return SHFileOperation(&FileOp) == 0;
}
int main()
{
    string pathFrom, pathTo;
    getline(cin, pathFrom);
    getline(cin, pathTo);
    copyFile_bySHFileOperation(pathFrom.append("\0\0").c_str(), pathTo.append("\0\0").c_str());
    /*
    可以同时复制多个文件，但中间以 '\0' 隔开，最后以两个 '\0' 结尾
    */

    return 0;
}
