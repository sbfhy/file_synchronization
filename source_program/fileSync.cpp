#include<iostream>
#include<string>
#include<io.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<windows.h>
using namespace std;

/* 从pathTo目录 同步到 pathFrom目录 */
void fileSync_to_from(string pathFrom, string pathTo)
{
    long handleTo = 0;
    struct  _finddata_t  fileInfoFrom, fileInfoTo;
    string pathNameFrom, pathNameTo;
    pathNameTo.assign(pathTo).append("\\*");
    if((handleTo = _findfirst(pathNameTo.c_str(), &fileInfoTo)) == -1)
        return ;

    do {
        if(!strcmp(fileInfoTo.name, ".") || !(strcmp(fileInfoTo.name, "..")))
            continue;
        pathNameFrom.assign(pathFrom).append("\\").append(fileInfoTo.name);
        pathNameTo.assign(pathTo).append("\\").append(fileInfoTo.name);
        if(fileInfoTo.attrib == _A_SUBDIR)
        {
            if(_findfirst(pathNameFrom.c_str(), &fileInfoFrom) == -1) {
                CreateDirectory(pathNameFrom.c_str(), NULL);
            }
            fileSync_to_from(pathNameFrom, pathNameTo);
        }
        else
        {
            if(_findfirst(pathNameFrom.c_str(), &fileInfoFrom) == -1) {
                CopyFile(pathNameTo.c_str(), pathNameFrom.c_str(), false);
            }
        }
    }while(_findnext(handleTo, &fileInfoTo) == 0);
    _findclose(handleTo);
    return ;
}

/* 文件同步，pathFrom目录 同步到 pathTo目录 */
void fileSync_from_to(string pathFrom, string pathTo)
{
    long handleFrom = 0;
    struct  _finddata_t  fileInfoFrom, fileInfoTo; /* 保存文件信息 */
    string pathNameFrom, pathNameTo;    /* 保存文件路径 */
    pathNameFrom.assign(pathFrom).append("\\*");
    if((handleFrom = _findfirst(pathNameFrom.c_str(), &fileInfoFrom)) == -1)
        return ;    /* 第一次没找到，即没有这个文件，退出 */

    do {
        if(!strcmp(fileInfoFrom.name, ".") || !strcmp(fileInfoFrom.name, ".."))
            continue;   /* 对于 . 和 .. 目录，直接跳过 */

        pathNameFrom.assign(pathFrom).append("\\").append(fileInfoFrom.name);
        pathNameTo.assign(pathTo).append("\\").append(fileInfoFrom.name);
        if(fileInfoFrom.attrib == _A_SUBDIR)   /* 如果这是个文件夹 */
        {
            if(_findfirst(pathNameTo.c_str(), &fileInfoTo) == -1) { /* 如果在pathFrom目录中没有对应的文件夹，就创建一个对应的文件夹 */
                CreateDirectory(pathNameTo.c_str(), NULL);
            }
            fileSync_from_to(pathNameFrom, pathNameTo); /* 继续进入搜索 */
        }
        else    /* 是个文件 */
        {
            if(_findfirst(pathNameTo.c_str(), &fileInfoTo) == -1) { /* 没找到直接复制过去 */
                CopyFile(pathNameFrom.c_str(), pathNameTo.c_str(), false);
            }
            else { /* 如果pathTo目录中有同名文件，则两者中取最后一次被修改时间晚的，覆盖掉另一个 */
                if(fileInfoFrom.time_write > fileInfoTo.time_write)
                    CopyFile(pathNameFrom.c_str(), pathNameTo.c_str(), false);
                else
                    CopyFile(pathNameTo.c_str(), pathNameFrom.c_str(), false);
            }
        }
    }while(_findnext(handleFrom, &fileInfoFrom) == 0);
    _findclose(handleFrom);
    return ;
}

int main()
{
    string pathFrom, pathTo;
    getline(cin, pathFrom);
    getline(cin, pathTo);
    fileSync_from_to(pathFrom, pathTo);
    fileSync_to_from(pathFrom, pathTo);

    system("pause");
    return 0;
}
