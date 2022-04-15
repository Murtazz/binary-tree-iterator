#ifndef _TREE_H_
#define _TREE_H_

class Tree {
  struct TreeNode;
  TreeNode *root;

 public:
  Tree();
  ~Tree();

  void insert (int data);

  class Iterator {
    TreeNode *p;
    explicit Iterator (TreeNode *p): p{p} {}
   public:
    int &operator*() const;

    bool operator==(const Iterator &other) const;

    bool operator!=(const Iterator &other) const;
    
    Iterator &operator++();

    friend class Tree;
  };

  Iterator begin();
  Iterator end();
};

#endif
