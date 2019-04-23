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


//��һ��ɨ���ļ����ַ�Ƶ�� 
bool scanCharacter(string waitingToCompressFileName, 
	string compressedFileName, FileInfo& fileInfo);
	
//��ȡѹ���ļ��ڵ���Ϣ 
bool readFileInfo(FileInfo &fileInfo, ifstream &in, map<string, char> references);

//������������ 
HuffmanTree buildHuffmanTree();
//������������,����map 
void travelHuffmanTree(HuffmanTree HT, map<char, string> &references, string s);
void travelHuffmanTree(HuffmanTree HT, map<string, char> &references, string s);

bool compress(string waitingToCompressFileName, string compressedFileName);
bool extract(string waitingToExtractFileName, string extractedFileName);

//ѹ���ļ����Ĳ��� 
bool compressCore(string waitingToCompressFileName, string compressedFileName, map<char, string> references);
//��ѹ�ļ����Ĳ��� 
bool extractCore(ifstream &in, string extractedFileName,
			map<string, char> &references, FileInfo &fileinfo, HuffmanTree HT);
//�����������ʾ��Ϣ 
void operated(); 

#endif
