#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void rotateLeft(AVLNode<Key, Value>* x);
    virtual void rotateRight(AVLNode<Key, Value>* x); 
    virtual void rebalance(AVLNode<Key, Value>* node);
    
};


// x - the unbalanced node
// y - the child that becomes the new root of the subtree
// B - the middle subtree that gets moved 

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* x){

  if (x == nullptr){
    return;
  }

  AVLNode<Key, Value>* y = x->getRight();
  
  if (y == nullptr){
    return;
  }

  AVLNode<Key, Value>* B = y->getLeft();
  AVLNode<Key, Value>* parent = x->getParent();

  y->setParent(parent);
  if (parent == nullptr){
    this->root_ = y;

  } else if (parent->getLeft()== x){
    parent->setLeft(y);

  } else {
    parent->setRight(y);
  }

  y->setLeft(x);
  x->setParent(y);

  x->setRight(B);
  if (B != nullptr){
    B->setParent(x);
  }

  // int8_t = y_bal = y->getBalance();
  // int8_t = x_bal = x->getBalance();

  // if (y_bal <= 0){
  //   x->setBalance(x_bal + 1 - std::min<int8_t>(0, yb));
  //   y->setBalance(y_bal + 1);
  // } else {
  //   x->setBalance(x_bal + 1);
  //   y->setBalance(y_bal + 1 + std::max<int8_t>(0, x->getBalance()));
  // }

}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* x){

  if (x == nullptr){
    return;
  }

  Node<Key, Value>*y = x->getLeft();
  if (y == nullptr){
    return;
  }

  Node<Key, Value>* B = y->getRight();
  Node<Key, Value>* parent = x->getParent();

  y->setParent(parent);
  if (parent == nullptr){
    this->root_ = y;
  
  } else if (parent->getLeft() == x){
    parent->setLeft(y);

  } else {
    parent->setRight(y);
  }

  y->setRight(x);
  x->setParent(y);

  x->setLeft(B);
  if (B != nullptr){
    B->setParent(x);
  }

  // int8_t = y_bal = y->getBalance();
  // int8_t = x_bal = x->getBalance();

  // if (y_bal >= 0){
  //   x->setBalance(x_bal - 1 + std::min<int8_t>(0, yb));
  //   y->setBalance(y_bal - 1);
  // } else {
  //   x->setBalance(x_bal - 1);
  //   y->setBalance(y_bal - 1 - std::max<int8_t>(0, x->getBalance()));
  // }

}

template<class Key, class Value>
void AVLTree<Key, Value>::rebalance(AVLNode<Key, Value>* node){
  
  // if (node == nullptr){
  //   return;
  // }

  // int8_t bal = node->getBalance();

  // //Left heavy (balance = +2)
  // if (bal == 2){
  //   AVLNode<Key, Value>* L = node->getLeft();

  //   //LR
  //   if (L->getBalance() == -1){
  //     rotateLeft(L);

  //     AVLNode<Key, Value>* x = L->getParent();

  //     if (x->getBalance() == 1){

  //       node->setBalance(-1);
  //       L->setBalance(0);

  //     } else if (x->getBalance() == -1){
        
  //       node->setBalance(0);
  //       L->setBalance(1);

  //     } else {
  //       node->setBalance(0);
  //       L->setBalance(0);
  //     }

  //     x->setBalance(0);
  //     rotateRight(node);
  //     return;

  //   }

  //   //LL
  //   rotateRight(node);
  //   node->setBalance(0);
  //   L->setBalance(0);
  //   return;

  // }

  // if (bal == -2){
    
  //   AVLNode<Key, Value>* R = node->getRight();

  //   if (R->getBalance() == 1){

  //     rotateRight(R);

  //     AVLNode<Key, Value>* x = R->getParent();

  //     if (x->getBalance() == 1){

  //       node->setBalance(0);
  //       R->setBalance(-1);

  //     } else if (x->getBalance() == -1){
  //       node->setBalance(1);
  //       R->setBalance(0);

  //     } else {
  //       node->setBalance(0);
  //       R->setBalance(0);
  //     }

  //     x->setBalance(0);
  //     rotateLeft(node);
  //     return;

  //   }


  //   rotateLeft(node);
  //   node->setBalance(0);
  //   R->setBalance(0);
  //   return;


  // }

  if (node == nullptr){
    return;
  }

  int8_t b = node->getBalance();

  if (b == 2){
    AVLNode<Key, Value>* L = node->getLeft();

    if (L->getBalance() < 0){
      rotateLeft(L);
    }

    rotateRight(node);

  } else if (b == -2){
    AVLNode<Key, Value>* R = node->getRight();

    if (R->getBalance() > 0){
      rotateRight(R);

    }

    rotateLeft(node);
  }

}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
  Key key = new_item.first;
  Value val = new_item.second;

  //CASE 1: Empty tree, new root 
  if (this->root_ == nullptr){
    this->root_ = new AVLNode<Key, Value>(key, val, nullptr);
    return;
  }

  //CASE 2: Normal BST Insertion
  Node<Key, Value>* curr = this->root_;
  Node<Key, Value>* parent = nullptr;

  while (curr != nullptr){
    parent = curr;
    if (key < curr->getKey()){
      curr = curr->getLeft();
      
    } else if (key > curr->getKey()){
      curr = curr->getRight();
    } else {
      curr->setValue(val);
      return;
    }
  }

  AVLNode<Key, Value>* p = static_cast<AVLNode<Key, Value>*>(parent);
  AVLNode<Key, Value>* newN = new AVLNode<Key, Value>(key, val, p);

  if (key < parent->getKey()){
    
    parent->setLeft(newN);

  } else {

    parent->setRight(newN);

  }

  AVLNode<Key, Value>* node = newN;

  while (p != nullptr){
    p->updateBalance(node == p->getLeft() ? 1 : -1);

    if (p->getBalance() == 0 ){
      node = p;
      p = p->getParent();
      continue;
    }
    
    if (p->getBalance() == 2 || p->getBalance() == -2){
      rebalance(p);
      break;
    }

    node = p;
    p = p->getParent();

  }
  

  

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    if (!curr){
      return;
    }

    if (curr->getLeft() != nullptr && curr->getRight() != nullptr){
      AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr));
      
      this->nodeSwap(curr, pred);
      curr = pred;

    }

    AVLNode<Key, Value>* parent = curr->getParent();
    AVLNode<Key, Value>* child = (curr->getLeft() != nullptr ? curr->getLeft() : curr->getRight());

    bool removeLeft = false;

    if (child != nullptr){
      
      child->setParent(parent);

      if (curr == this->root_){
        this->root_ = child;

      } else if (parent->getLeft() == curr){
        parent->setLeft(child);
        removeLeft = true;

      } else {
        parent->setRight(child);
        removeLeft = false;

      }

    } else {

      if (parent == nullptr){
        this->root_ = nullptr;
      } else if (parent->getLeft() == curr){
        parent->setLeft(nullptr);
        removeLeft = true;
      } else {
        parent->setRight(nullptr);
        removeLeft = false;
      }
    
    }

    delete curr;

    AVLNode<Key, Value>* x = parent;
      while (x != nullptr){

        x->updateBalance(removeLeft ? +1 : -1);

        int bal = x->getBalance();

        
        if (bal == 0){
          removeLeft = (x->getParent() && x->getParent()->getLeft() == x);
          continue;
        } 

        if (bal == 1 || bal == -1){
          break;
        }


        AVLNode<Key, Value>* p = x->getParent();
        rebalance(x);

        if ( p == nullptr){
          break;
        }

        x = p;

        removeLeft = (x->getParent() && x->getParent()->getLeft() == x);

    
      }

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
