//
//  BinarySearchTree.hpp
//  BinarySearchTree
//
//  Created by mov on 11/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//
/*
 注意，使用模板的话，必须将声明和实现都放在头文件中，不然找不到函数的实现会报错；
 或者下策：在需要用的文件中包含cpp文件；
 */
#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

template<class T> struct TreeNode
{
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
};

template<class T> class BinarySearchTree{
private:
    TreeNode<T>* root;
    long size;
    TreeNode<T>* precursor(TreeNode<T> * p);
    TreeNode<T>* succeed(TreeNode<T> * p);
    void transplant(TreeNode<T> * p,TreeNode<T> * q);
    TreeNode<T>* copy(TreeNode<T> * p,TreeNode<T> * f);
    
public:
    BinarySearchTree(){
        root = nullptr;
        size=0;
    }
    //拷贝构造函数；
    BinarySearchTree(const BinarySearchTree& C)
    {
        root=copy(C.root, nullptr);
        size=C.size;
    }
    ~BinarySearchTree(){
        TreeNode<T>* stack[size];
        long top=-1;
        if(root)
            stack[++top]=root;
        while(top>=0)
        {
            TreeNode<T>* p=stack[top--];
            if(p->right)               //需要先遍历左子树，所以右子树先进栈；
                stack[++top]=p->right;
            if(p->left)
                stack[++top]=p->left;
            delete p;
        }
    }
    void insertVal(T value);
    void deleteVal(T value);
    TreeNode<T> * search(T value);
    void inorder();
    void preorder();
    void layerorder();
    void postorder();
};

#endif /* BinarySearchTree_hpp */
