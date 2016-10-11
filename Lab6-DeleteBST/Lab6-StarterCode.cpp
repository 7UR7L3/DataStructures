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
int value = 30;	
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
	deleteNode(root, value);
cout<<"Pre Order Traversal:"<<endl;
	preOrderTraversal(root);
	cout<<endl<<"In Order Traversal:"<<endl;
	inOrderTraversal(root);
	cout<<endl<<"Post Order Traversal:"<<endl;
	postOrderTraversal(root);

	deleteAndReplaceMinRight(root,value);
	cout<<"Pre Order Traversal:"<<endl;
	preOrderTraversal(root);
	cout<<endl<<"In Order Traversal:"<<endl;
	inOrderTraversal(root);
	cout<<endl<<"Post Order Traversal:"<<endl;
	postOrderTraversal(root);
	return 0;
}
//---------------------TO DO----------------------
void deleteNode(TreeNode *node, int key) {
	// Implement your code here

}


//---------------------TO DO----------------------
void deleteAndReplaceMinRight(TreeNode *node, int key) {
	// Implement your code here

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

