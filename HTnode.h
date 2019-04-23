
struct HTnode{
	int key; //权重 
	char element;
	std::string code;
	HTnode* lchild = NULL;
	HTnode* rchild = NULL; 
	
	friend bool operator < (const HTnode &a, const HTnode &b)
    {
        return a.key > b.key;//小的优先级高
    }

};
typedef HTnode* HuffmanTree;
