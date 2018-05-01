//
//  BlackRedTree.hpp
//  BlackRedTree
//
//  Created by mov on 12/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//

#ifndef BlackRedTree_hpp
#define BlackRedTree_hpp

template<class T> struct TreeNode
{
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
    bool color; // true:black  false:red
    //TreeNode(): color(true){}
};

template<class T> class RBTree{
private:
    TreeNode<T>* root;
    long size;
    TreeNode<T>* NIL=new TreeNode<T>; //利用TreeNode的构造，NIL已经满足要求；
    TreeNode<T>* precursor(TreeNode<T> * p);
    TreeNode<T>* succeed(TreeNode<T> * p);
    void transplant(TreeNode<T> * p,TreeNode<T> * q);
    TreeNode<T>* copy(TreeNode<T> * p,TreeNode<T> * f,const RBTree& C);
    void RB_INSERT_FIXUP(TreeNode<T> * z);
    void RB_DELETE_FIXUP(TreeNode<T> * x);
    void LEFT_ROTATE(TreeNode<T> * x);
    void RIGHT_ROTATE(TreeNode<T> * x);
    
public:
    RBTree(){
        root = NIL;
        NIL->left=NIL;
        NIL->right=NIL;
        NIL->parent=NIL;
        NIL->color=true;
        size=0;
    }
    //拷贝构造函数；
    RBTree(const RBTree& C)
    {
        NIL->left=NIL;
        NIL->right=NIL;
        NIL->parent=NIL;
        NIL->color=true;
        root=copy(C.root, C.NIL, C);
        size=C.size;
    }
    ~RBTree(){
        TreeNode<T>* stack[size];
        long top=-1;
        if(root!=NIL)
            stack[++top]=root;
        while(top>=0)
        {
            TreeNode<T>* p=stack[top--];
            if(p->right!=NIL)              //需要先遍历左子树，所以右子树先进栈；
                stack[++top]=p->right;
            if(p->left!=NIL)
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

#endif /* BlackRedTree_hpp */
