#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

bool checkEqualPaths(Node* root, int depth, int &leafDepth){

  if (root == NULL){
    return true; //empty subtree is balanced by definition
  
  }

  if (root->left == nullptr && root->right == nullptr){ //indicator of a leaf node 
  
    if (leafDepth == -1){
      leafDepth = depth; //if this is the first leaf we encounter, make sure to record its depth
      return true;
    }

    //Check if the leaf's depth matches the first leaf's depth
    return depth == leafDepth;

  }

  bool leftEqual = true;
  bool rightEqual = true;

  if (root->left){
    leftEqual = checkEqualPaths(root->left, depth + 1, leafDepth);
  }
  if (root->right){
    rightEqual = checkEqualPaths(root->right, depth +1, leafDepth);
  }

  return leftEqual && rightEqual;

}

/**
 * @brief Returns true if all paths from leaves to root are the same length (height),
 *        and false otherwise
 *
 *        Note: this doesn't mean we are checking if the tree is full, but just that
 *        any leaf node (wherever it may exist) has the same length path to the root 
 *        as all others.
 * 
 * @param root Pointer to the root of the tree to check for equal paths
 */

bool equalPaths(Node * root)
{
  // Add your code below
  int leafDepth = -1; //initializing first leaf depth 
  return checkEqualPaths(root, 0, leafDepth);


}

