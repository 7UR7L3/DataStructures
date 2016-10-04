#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Return the total number of nodes in the BST.
int getSize(Node* node);
// Return the minimal value in the BST.
int getminValue(Node* node);
// Return the maximum depth of a path in the tree.
int getmaxDepth(Node* node);

// print the tree starting the youngest(smallest) child.
void printTree(Node* node);
// Insert the new value into the BST in the correct position.
Node *newNode(int data);
// add data given the root (parent)
Node *addNode(Node* node, int data);


int main (int argc, char* argv[]){
  Node* root = NULL;

  root = newNode(5);
  
  addNode(root,3); //left child to 5
  addNode(root,9); //right child to 5

  addNode(root,1); //left child to 3
  addNode(root,4); //right child to 3

  addNode(root,6); //left child to 9

  addNode(root, 2); //left child to 4

  printTree(root);
  cout << endl << "There are " << getSize(root) << " nodes in the tree" << endl;
  cout << "The minimum value node is:  " << getminValue(root) << endl;
  cout << "There max depth is: " << getmaxDepth(root) << endl;
}


Node *newNode(int data) {
  Node* node = new Node;
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

Node *addNode(Node* node, int data) {
  bool left = data < node->data;
  if( left )
  {
    if( node->left == NULL )
    {
      node->left = newNode( data );
      return node->left;
    }
  }
  else
  {
    if( node->right == NULL )
    {
      node->right = newNode( data );
      return node->right;
    }
  }
  addNode( left ? node->left : node->right, data );
  return NULL;
}

int getSize(Node* node) {
  if( node == NULL ) return 0;
  return 1+getSize(node->left)+getSize(node->right);
}

int min( int a, int b, int c )
{
  int out = a;
  if( b < out ) out = b;
  if( c < out ) out = c;
  return out;
}

int getminValue(Node* node) {
  if( node->left == NULL && node->right == NULL ) return node->data;
  int l = node->left != NULL ? getminValue( node->left ) : node->data;
  int r = node->right != NULL ? getminValue( node->right ) : node->data;
  return min( node->data, l, r );
}

void printTree(Node* node) {
  if( node == NULL ) return;
  printTree( node->left );
  cout << node->data << " " << endl;
  printTree( node->right );
}

int getmaxDepth(Node* node) {
  if( node == NULL ) return 0;
  int l = getmaxDepth( node->left );
  int r = getmaxDepth( node->right );
  return 1 + ( l < r ? r : l );
}

