#ifndef REDBLACK_H
#define REDBLACK_H

struct RedBlackNode
{
	bool colour;
	int key;
	RedBlackNode* left;
	RedBlackNode* right;
	RedBlackNode* parent;
	RedBlackNode( RedBlackNode* p, bool c, int k )
	{
		colour = c;
		key = k;
		parent = p;
	}
};

class RedBlackTree
{
private:
	RedBlackNode* root;
	void leftRotate(RedBlackNode* node);
	void rightRotate(RedBlackNode* node);
	void insertRB(int value);
	void rbBalance(RedBlackNode* node);
public:
	void init();
	void redBlackInsert(int value);
	void redBlackDelete(int value);
	RedBlackNode* search(int value);
	void deleteTree();
};

#endif // REDBLACK_H
