
struct HTnode{
	int key; //Ȩ�� 
	char element;
	std::string code;
	HTnode* lchild = NULL;
	HTnode* rchild = NULL; 
	
	friend bool operator < (const HTnode &a, const HTnode &b)
    {
        return a.key > b.key;//С�����ȼ���
    }

};
typedef HTnode* HuffmanTree;
