/*
    C++ 遍历某个文件夹下所有文件
*/
#include<iostream>
#include<string>
#include<io.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

void fileSearch(string path)
{
    long hFile = 0;
    /*
        _finddata_t  存储文件各种信息的结构体，<io.h>;
    */
    struct _finddata_t fileInfo;
    string pathName;
    /*
        \\* 表示符合的所有文件;
        没有找到即文件夹为空，退出;
        assign 表示把 pathName清空并置为path;
        append 表示在末尾加上字符串;
        c_str 返回一个const char* 的临时指针;
        _findfirst
            搜索与指定的文件名称匹配的第一个实例，若成功则返回第一个实例的句柄，否则返回-1L;
            函数原型：long _findfirst( char *filespec, struct _finddata_t *fileinfo );
    */
    if ( ( hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo) ) == -1)
        return ;

    do {
        cout << path+"\\"+fileInfo.name << endl;
        /*
            文件夹下有 . 和 .. 目录，不能进入搜索;
            _A_SUBDIR 表示文件夹属性;
        */
        if( strcmp(fileInfo.name,"..") && strcmp(fileInfo.name,".") && fileInfo.attrib==_A_SUBDIR )
            fileSearch(path+"\\"+fileInfo.name);
    } while ( _findnext(hFile, &fileInfo) == 0 );
    /*
        _findnext 搜索与_findfirst函数提供的文件名称匹配的下一个实例，若成功则返回0，否则返回－1 ;
        _findclose 结束查找;
    */
    _findclose(hFile);
    return ;
}
int main()
{
    string path="E:\\Git";
    fileSearch(path);

    system("pause");
    return 0;
}
