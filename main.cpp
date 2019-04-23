#include"main.h"
#include<time.h> 
//��Ź��������ڵ�ָ���vector 
vector<HTnode*> q;
//Ϊ�˷�����������õ�·�� 
const string ROOT_DIRECTORY = "";

bool cmp1(HTnode* a, HTnode* b){
	return a->key > b->key;
}
void homePage(){
	printf("******************************************\n");
	printf("��ӭʹ��ѹ���ļ�ϵͳ       By AKA.PangHu *\n");
	printf("1.ѹ���ļ�                               *\n");
	printf("2.�����ļ�                               *\n");
	printf("3.�˳�                                   *\n"); 
	printf("******************************************\n");
	printf("������������еĲ������:");
	
	string t;
	cin >> t;
	if(t == "1"){
		bool error = false;
		string waitingToCompressFileName, compressedFileName;
		printf("��������Ҫѹ�����ļ�����:");
		cin >> waitingToCompressFileName;
		printf("������ѹ�����ļ�������:");
		cin >> compressedFileName;
		clock_t start = clock();
		cout << "ѹ����ʼʱ��:" << start << endl; 
		error = compress(waitingToCompressFileName, compressedFileName);
		clock_t end = clock();
		cout << "ѹ������ʱ�䣺" << end << endl; 
		cout << "ѹ����ʱ����:" << end - start << endl; 
		if(!error) operated();
	} 
	else if(t == "2"){
		bool error = false;
		string waitingToExtractFileName, extractedFileName;
		printf("��������Ҫ��ѹ���ļ�����:");
		cin >> waitingToExtractFileName;
		printf("�������ѹ���ļ�������:");
		cin >> extractedFileName;
		clock_t start = clock();
		cout << "��ѹ��ʼʱ��:" << start << endl; 
		error = extract(waitingToExtractFileName, extractedFileName);
		clock_t end = clock();
		cout << "��ѹ����ʱ�䣺" << end << endl; 
		cout << "��ѹ��ʱ����:" << end - start << endl; 
		if(!error) operated();
	}
	else if(t == "3"){
		exit(0); 
	} 
	else{
		printf("�������ݴ���, ����������!\n"); 
	}
}
//O(N)
bool scanCharacter(string waitingToCompressFileName, 
	string compressedFileName, FileInfo& fileInfo){
	string s;
	ifstream myfile(ROOT_DIRECTORY + waitingToCompressFileName, ios::binary); 
	ofstream out(ROOT_DIRECTORY + compressedFileName, ios::binary);
	if(!myfile.is_open() || !out.is_open()){
		cout << "�����ļ�������! ������������" << endl; 
		return true;
	} 
	map<char, int> mapp;
	char ch;
	while(myfile.get(ch)){
		mapp[ch]++;
		fileInfo.characterNum++;
	}
	for(auto it : mapp) fileInfo.characterType++;

	out.write((char*)&(fileInfo.characterNum), sizeof(int));
	out.write((char*)&(fileInfo.characterType), sizeof(int));

	for(auto it : mapp){ 
		HTnode* node = new HTnode;
		node->element = it.first;
		node->key = it.second;
		q.push_back(node);
		out.write((char*)&(node->element), sizeof(char));
		out.write((char*)&(node->key), sizeof(int));
	}
	myfile.close();
	out.close();
	return false;
}

//!!!!!!O(N^3) ����N������ 
HuffmanTree buildHuffmanTree(){
	int n = q.size();
	for(int i = 0; i < n - 1; i++){
		//���Ի����Լ�ʵ�ֵ����� 
		sort(q.begin(), q.end(), cmp1);
		HTnode *x, *y;
		HTnode *node = new HTnode;
		node->lchild = x = q.back(); q.pop_back();
		node->rchild = y = q.back(); q.pop_back();
		node->key = x->key + y->key;
		q.push_back(node);
	}
	HTnode* t = q.back();
	return t;
}
void travelHuffmanTree(HuffmanTree HT, map<char, string> &references, string s){
	if(!HT->lchild && !HT->rchild){
		HT->code = s;
		references[HT->element] = s; 
		return;
	}
	if(HT->lchild) travelHuffmanTree(HT->lchild, references, s + "0");
	if(HT->rchild) travelHuffmanTree(HT->rchild, references, s + "1");
}
void travelHuffmanTree(HuffmanTree HT, map<string, char> &references, string s){
	if(!HT->lchild && !HT->rchild){
		HT->code = s;
		references[s] = HT->element; 
		return;
	}
	if(HT->lchild) travelHuffmanTree(HT->lchild, references, s + "0");
	if(HT->rchild) travelHuffmanTree(HT->rchild, references, s + "1");
}
//O(N)
bool compressCore(string waitingToCompressFileName, string compressedFileName, map<char, string> references){
	ifstream in(ROOT_DIRECTORY + waitingToCompressFileName, ios::binary);
	ofstream out(ROOT_DIRECTORY + compressedFileName, ios::binary | ios::app);
	if(!in.is_open() || !out.is_open()){
		cout << "�����ļ�������! ������������" << endl; 
		return true;
	}
	unsigned char char_temp = '\0';
	string unit = "";
	while(1){
		char_temp = in.get();
		if(in.eof()) break;
		unit += references[char_temp];
		while(unit.length() >= 8){
			char_temp = '\0';
			for(int i = 0; i < 8; i++){
				char_temp = char_temp << 1;
				if(unit[i] == '1') char_temp = char_temp | 1;
			}
			auto p = unit.begin();
			unit.erase(p, p + 8);//���unit�е�ǰ��λ����
			out.write((char*)&char_temp, sizeof(unsigned char));//�����й�����������Ϣ���ַ�д�뵽ѹ���ļ���ȥ
		}
	}
	/////////////////////////////////////////
	if(unit.length() > 0){
		char_temp = '\0';
		for(int i = 0; i < unit.length(); i++){
			char_temp = char_temp << 1;
			if(unit[i] == '1') char_temp = char_temp | 1;
		}
		for(int i = 0; i < (8-unit.length()); i++) char_temp = char_temp << 1;
		out.write((char*)&char_temp, sizeof(unsigned char));
	}
	/////////////////////////////////////////
	q.resize(0);
	in.close();
	out.close();
	return false;
}
//O(N)
bool readFileInfo(FileInfo &fileInfo, ifstream &in, map<string, char> references){
	if(!in.is_open()){
		cout << "�����ļ�������! ������������" << endl; 
		return true;
	}
	
	//��ȡ��ѹ���ļ��е���Ƶ 
	in.read((char*)&fileInfo.characterNum, sizeof(int));
	in.read((char*)&fileInfo.characterType, sizeof(int));
	
	for(int i = 0; i < fileInfo.characterType; i++){
		HTnode* node = new HTnode;
		in.read((char*)&(node->element), sizeof(char));
		in.read((char*)&(node->key), sizeof(int));
		node->lchild = node->rchild = nullptr;
		q.push_back(node);
	}
	return false;
}

//O(NlogN)
bool extractCore(ifstream &in, string extractedFileName,
			map<string, char> &references, FileInfo &fileInfo, HuffmanTree HT){
//	ifstream in(ROOT_DIRECTORY + waitingToExtractFileName, ios::binary);
	ofstream out(ROOT_DIRECTORY + extractedFileName, ios::binary);
	if(!in.is_open() || !out.is_open()){
		cout << "�����ļ�������! ������������" << endl; 
		return true;
	}
	string unit = "";
	HuffmanTree head = HT;
	unsigned char char_temp = '\0';
	while(fileInfo.characterNum){
		
		char_temp = in.get();
		if(in.eof()) break;
		for(int i = 0; i < 8; i++){
			if(!fileInfo.characterNum) break;
			
			if(head->lchild == nullptr && head->rchild == nullptr){
				out.write((char*)&head->element, sizeof(unsigned char));
				fileInfo.characterNum--;
				head = HT;
			}
			if(char_temp & 128){
				head = head->rchild;
			} 
			else{
				head = head->lchild;
			}

		    char_temp = char_temp << 1;
		}
	}
		
	//�ͷſռ䣬�ر��� 
	q.resize(0);
	in.close();
	out.close();
	return false;
}

void operated(){
	printf("�����ɹ�!\n");
	printf("�˳�����������0 �����������������1\n");
	string s; cin >> s;
	if(s == "0"){
		exit(0); 
	} 
	else if(s == "1"){
		return;
	}
	else{
		cout << "δ֪����,������������." << endl;
	}
}
bool compress(string waitingToCompressFileName, string compressedFileName){
		bool error = false;
		FileInfo fileInfo;
		map<char, string> references;
		error = scanCharacter(waitingToCompressFileName, compressedFileName, fileInfo);
		if(error) return error;
		clock_t start = clock();
		cout << "������ʼʱ��:" << start << endl; 
		HuffmanTree HT = buildHuffmanTree();
		clock_t end = clock();
		cout << "��������ʱ�䣺" << end << endl; 
		cout << "��������������ʱ����:" << end - start << endl; 
		travelHuffmanTree(HT, references, "");
		error = compressCore(waitingToCompressFileName, compressedFileName, references);	
		return error;
}
bool extract(string waitingToExtractFileName, string extractedFileName){
		bool error = false;
		FileInfo fileInfo;
		map<string, char> references;
		ifstream in(ROOT_DIRECTORY + waitingToExtractFileName, ios::binary);  
		if(!in.is_open()){
			cout << "�����ļ�������! ������������" << endl; 
			return true;
		}
		clock_t start = clock();
		cout << "����Ϣ��ʼʱ��:" << start << endl; 
		readFileInfo(fileInfo, in, references);
		HuffmanTree HT = buildHuffmanTree();
		travelHuffmanTree(HT, references, "");
		clock_t end = clock();
		cout << "����Ϣ����ʱ�䣺" << end << endl; 
		cout << "����Ϣ��ʱ����:" << end - start << endl; 
	
		error = extractCore(in, extractedFileName, references, fileInfo, HT);
		 return error;
}
int main(){
	while(1){
		homePage();
	}
}
