#include <iostream>

using namespace std;
struct TreeNode
{
   int key;
   TreeNode *left;
   TreeNode *right;
   TreeNode *parent;
};

void deleteNode(TreeNode *node, int key);
void deleteAndReplaceMinRight(TreeNode *node, int key);
void preOrderTraversal(TreeNode *node);
void inOrderTraversal(TreeNode *node);
void postOrderTraversal(TreeNode *node);

int main() {
	TreeNode *root = NULL;
//test case input
int a[] = { 25, 15, 30, 28, 35, 27, 29, 33, 70};
int length = 9;
int value = 28;	
	//end of input
	
	for(int i=0; i<length; i++) {
		TreeNode *newnode = new TreeNode;
		newnode->key = a[i];
		newnode->left=NULL;
		newnode->right=NULL;
		newnode->parent = NULL;
		if(root == NULL) {
			root = newnode;
		}
		else {
			TreeNode *temp = root;
			TreeNode *temp2 = NULL;
			while(temp!=NULL) {
				temp2=temp;
				if(temp->key > a[i]) {
					temp = temp->left;
				}
				else {
					temp = temp->right;
				}
			}
			if(a[i]<temp2->key)
			{
			    newnode->parent = temp2;
			    temp2->left = newnode;
			}
			else
			{
			    newnode->parent = temp2;
			    temp2->right = newnode;
			}
		}
	}
	deleteNode(root, 30);
	cout<<"Pre Order Traversal:"<<endl;
	preOrderTraversal(root);
	cout<<endl<<"In Order Traversal:"<<endl;
	inOrderTraversal(root);
	cout<<endl<<"Post Order Traversal:"<<endl;
	postOrderTraversal(root);

	deleteAndReplaceMinRight(root,28);
	cout<<endl<<"Pre Order Traversal:"<<endl;
	preOrderTraversal(root);
	cout<<endl<<"In Order Traversal:"<<endl;
	inOrderTraversal(root);
	cout<<endl<<"Post Order Traversal:"<<endl;
	postOrderTraversal(root);
	cout<<endl;
	return 0;
}
//---------------------TO DO----------------------
void deleteNode(TreeNode *node, int key) {
	if( node == NULL ) return;
	if( node->key == key )
	{
		if( node->left == NULL && node->right == NULL )
		{
			if( node->parent == NULL )
			{
				node = NULL;
				delete node;
				return;
			}
			if( node->parent->left == node )
			{
				node->parent->left = NULL;
				delete node->parent->left;
			}
			else
			{
				node->parent->right = NULL;
				delete node->parent->right;
			}
		}
		else if( node->left == NULL )
		{
			if( node->parent == NULL )
			{
				node = node->right;
				node->parent = NULL;
				return;
			}
			if( node->parent->left == node ) node->parent->left = node->right;
			else node->parent->right = node->right;
			node->right->parent = node->parent;
			delete node;
		}
		else
		{
			TreeNode* n = node->left;
			int i = 0;
			while( n->right != NULL ){ n = n->right; i++; }
			node->key = n->key;
			if( i == 0 ) n->parent->left = NULL;
			else n->parent->right = NULL;
			delete n;
		}
	}
	deleteNode( node->left, key );
	deleteNode( node->right, key );
}


//---------------------TO DO----------------------
void deleteAndReplaceMinRight(TreeNode *node, int key)
{
	if( node == NULL ) return;
	if( node->key == key )
	{
		if( node->left == NULL && node->right == NULL )
		{
			if( node->parent == NULL )
			{
				node = NULL;
				delete node;
				return;
			}
			if( node->parent->left == node )
			{
				node->parent->left = NULL;
				delete node->parent->left;
			}
			else
			{
				node->parent->right = NULL;
				delete node->parent->right;
			}
		}
		else if( node->right == NULL )
		{
			if( node->parent == NULL )
			{
				node = node->left;
				node->parent = NULL;
				return;
			}
			if( node->parent->left == node ) node->parent->left = node->left;
			else node->parent->right = node->left;
			node->left->parent = node->parent;
			delete node;
		}
		else
		{
			TreeNode* n = node->right;
			int i = 0;
			while( n->left != NULL ) { n = n->left; i++; }
			node->key = n->key;
			if( i == 0 ) n->parent->right = NULL;
			else n->parent->left = NULL;
			delete n;
		}
	}
	deleteAndReplaceMinRight( node->left, key );
	deleteAndReplaceMinRight( node->right, key );
}

void preOrderTraversal(TreeNode *node)
{
	if(node == NULL)
		return;
	else
	{
		cout<<node->key<<" ";
		preOrderTraversal(node->left);
		preOrderTraversal(node->right);
	}
}
void inOrderTraversal(TreeNode *node)
{
	if(node == NULL)
		return;
	else
	{
		inOrderTraversal(node->left);
		cout<<node->key<<" ";
		inOrderTraversal(node->right);
	}
}
void postOrderTraversal(TreeNode *node)
{
	if(node == NULL)
		return;
	else
	{
		postOrderTraversal(node->left);
		postOrderTraversal(node->right);
		cout<<node->key<< " ";
	}
}