#include <ostream>
#include <iostream>
#include "tree.h"

struct Tree::TreeNode {
  int data;
  enum class Kind {Left, Right, Root};
  Kind kind;
  TreeNode *parent, *left, *right;
  
  TreeNode(int data, Kind kind, TreeNode *parent, TreeNode *left = nullptr, TreeNode *right = nullptr):
    data{data}, kind{kind}, parent{parent}, left{left}, right{right} {}
  ~TreeNode() {
    delete left;
    delete right;
  }
  
};
Tree::~Tree() {
  delete root;
}

void Tree::insert(int data) {
  TreeNode *prevN; // keeping track of parent
  TreeNode *newN = root;
  TreeNode::Kind treeKind = TreeNode::Kind::Root; // keeping track of TreeNode Type
  if (newN == nullptr) {
    root = new TreeNode(data, treeKind, nullptr);  // add to root if there is no root
  } else {
    while (newN != nullptr) {
      prevN = newN;
      if (data < newN->data) {  // left node type if less than current TreeNode
        newN = newN->left;
        treeKind = TreeNode::Kind::Left; 
      } else if (data > newN->data) {  // right node type if more than current TreeNode
        newN = newN->right; 
        treeKind = TreeNode::Kind::Right; 
      } else {  // if the integer already exists then do not insert
        return;
      }
    }
    newN = new TreeNode(data, treeKind, prevN);  
    if (treeKind == TreeNode::Kind::Left) {
      prevN->left = newN; // connect to the parent
    } else if (treeKind == TreeNode::Kind::Right) {
      prevN->right = newN; // connect to the parent
    }
  }
}

int &Tree::Iterator::operator*() const {
  return p->data;
}

bool Tree::Iterator::operator==(const Iterator &other) const {
  return p == other.p;
}

bool Tree::Iterator::operator!=(const Iterator &other) const {  
      return !(p == other.p);  // Not == operator
}

Tree::Iterator &Tree::Iterator::operator++() { // increment through the tree
  TreeNode *temp;
  if (p->right != nullptr) {  // if right node exists
    p = p->right;             // go to the right node
    while (p->left != nullptr) {  // then go to the far left of that node
      p = p->left;
    }
  } else {
    temp = p->parent;
    while (p->kind != TreeNode::Kind::Root && p->kind == TreeNode::Kind::Right) {  // if the the current node is not root 
      p = temp;                                    // and p is a right node move up one to the parent root
      temp = temp->parent;
    }
    p = temp;
  }
  return *this; // return the increment
}

Tree::Iterator Tree::begin() { // begins at the far left node
  TreeNode *begin = root;
  if (begin != nullptr) {  // nullptr then Tree is empty
    while (begin->left != nullptr) {
      begin = begin->left;
    }
  }
  return Iterator {begin};
}

Tree::Iterator Tree::end() { // ends with a nullptr
  return Iterator {nullptr};
}

Tree::Tree(): root{nullptr} {}
