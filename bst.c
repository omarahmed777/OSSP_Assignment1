#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//Defining structure of node
typedef struct _Node {
  struct _Node *left;
  struct _Node *right;
  int value;
} Node;

/* addNode Helper Function
 * Creates a new node
 * Returns created node to insert
 */
Node *newNode(int value) {
  Node *temp = malloc(sizeof(Node));
  temp->value = value;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}


/* Add Node Function
 * Inserts node into tree
 * Returns created leaf
 */
Node * addNode(Node *root, int value) {
  if (root == NULL){ //If no root exists, create a new one
    return newNode(value);
  }
  /* There are two cases to save a root, either:
   * 1. The current node has no child in that space
   *     so it is safe to save it there, or:
   * 2. There is a node occupying that space
   *     so you should recurse another level without saving anything
   */
  else if (value > root->value) { //value > root, so left subtree
    if (root->left == NULL) //No child, safe to save
      root->left = addNode(root->left, value);
    else //Child is occuyping space, recurse further down
      addNode(root->left, value);
  }
  else if (value < root->value) { //value < root, so right subtree
    if (root->right == NULL) //No child, safe to save
      root->right = addNode(root->right, value);
    else //Child is occuyping space, recurse further down
      addNode(root->right, value);
  }
  else { //Element already in tree
    return NULL;
  }
}

/* removeNode Helper Function
 * Finds inorder successor (rightmost of left subtree) when deleting node w/ 2 children
 * Returns rightmost node of left subtree
 */
Node* minLeftNode(Node* node) {
  Node* currentNode = node; //Keep track of current node
  
  // While there exists a current node AND the node still has a right child
  // (The smallest node in the left tree will not have a right child)
  while (currentNode != NULL  && currentNode->right != NULL) {
    currentNode = currentNode->right;
  }
  return currentNode;
}

/* Remove Node Function
 * Removes node passed into the function
 * Returns root of tree/new root of tree if root was deleted
 */
Node * removeNode(Node *root, int value) {
  if (root == NULL) { //Base case, attempting to delete NULL
    return root;
  }
  if (value > root->value) { //Element is located in left subtree
    root->left = removeNode(root->left, value);
  }
  else if (value < root->value) { //Element is located in right subtree
    root->right = removeNode(root->right, value);
  }
  else { //Element is found
    // 0 Children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
      return(NULL);
    }
    //One child
    else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }
    else if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    //Two children
    else {
      Node *temp = minLeftNode(root->left);
      root->value = temp->value;
      root->left = removeNode(root->left, temp->value);
    }
  }
  return root;
}

//Displays a subtree's contents
void displaySubtree(Node * N) {
  if (N == NULL) //If an empty node is reached, return
    return;
  else { //Otherwise, traverse fully down right, then node, then left
    displaySubtree(N->right);
    printf("%d\n", N->value);
    displaySubtree(N->left);
  }
}

/* Counts number of leaves in the tree
* A leaf node is a node with no child nodes
*/
int numberLeaves(Node * N) {
  if (N == NULL) //Base case. Checking if root is NULL
    return 0;
  if (N->left == NULL && N->right == NULL) //Check for leaf node
    return 1;
  //Otherwise, recurse and add
  return numberLeaves(N->left) + numberLeaves(N->right);
}

// Removes entire subtree
Node * removeSubtree(Node * root, int value) {
  
  if (!root) //Base case. No subtree means no deletion
    return NULL;
  if (root->value == value) { //If root of subtree to be deleted is found
    removeSubtree(root->left, value); //Traverse down, deleting everything
    removeSubtree(root->right, value);
    free(root);
    root = NULL;
  }
  else { 
    if (value > root->value) //If value >, then it will be in left subtree
      root->left = removeSubtree(root->left, value);
    else if (value < root->value)//Otherwise it will be in right subtree
      root->right = removeSubtree(root->right, value);
  }
  return root;
}

/* nodeDepth Helper Function
* Recursively adds depth every time a level is traversed
* Returns depth of inputted node
*/
int findDepth(Node * N, int value){
  if (N == NULL) //If traversed N is null, depth = 0
    return 0;
  if (N->value == value) //If node is found, do not add depth as a new level is not accessed
    return 0;
  if (N->value < value) //Otherwise, add 1 to the depth and traverse down another level
    return 1 + findDepth(N->right, value);
  else if (N->value > value)
    return 1 + findDepth(N->left, value);
}

/* Calculates depth of inputted node N respective to root node R
* Returns depth of node N using helper function findDepth
*/
int nodeDepth(Node * R, Node * N){
  //If R is NULL, tree is empty; so depth = -1
  if (R == NULL || N == NULL) //If *FIRST* N = NULL, then you cannot calculate its depth
    return -1;
  else if (N == R)
    return 0;
  else
    return findDepth(R, N->value);
}
