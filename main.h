#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<malloc.h>
#include<map>
#include<queue>
#include"FileInfo.h"
#include"HTnode.h"
 
using namespace std;


//第一次扫描文件的字符频率 
bool scanCharacter(string waitingToCompressFileName, 
	string compressedFileName, FileInfo& fileInfo);
	
//读取压缩文件内的信息 
bool readFileInfo(FileInfo &fileInfo, ifstream &in, map<string, char> references);

//构建哈夫曼树 
HuffmanTree buildHuffmanTree();
//遍历哈夫曼树,生成map 
void travelHuffmanTree(HuffmanTree HT, map<char, string> &references, string s);
void travelHuffmanTree(HuffmanTree HT, map<string, char> &references, string s);

bool compress(string waitingToCompressFileName, string compressedFileName);
bool extract(string waitingToExtractFileName, string extractedFileName);

//压缩文件核心部分 
bool compressCore(string waitingToCompressFileName, string compressedFileName, map<char, string> references);
//解压文件核心部分 
bool extractCore(ifstream &in, string extractedFileName,
			map<string, char> &references, FileInfo &fileinfo, HuffmanTree HT);
//操作后输出提示信息 
void operated(); 

#endif
