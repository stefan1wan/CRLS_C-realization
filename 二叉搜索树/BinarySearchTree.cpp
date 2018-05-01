//
//  BinarySearchTree.cpp
//  BinarySearchTree
//
//  Created by mov on 11/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//

#include "BinarySearchTree.hpp"
#include <iostream>

/* 为了提高效率，主要的函数都采用非递归方式实现 */
template<class T> void BinarySearchTree<T>::insertVal(T value){
    TreeNode<T>* p=root;
    TreeNode<T>* f=nullptr;
    /* f记录当前节点的父节点，当p为空指针时，停止循环*/
    while(p){
        if(value==p->val)
            return;
        else if(value<p->val){
            f=p;
            p=p->left;}
        else{
            f=p;
            p=p->right;}
    }
    
    size++; //程序执行到这里，说明没有找到相同的值；
    
    /*以p为指针，建立新的节点*/
    p= new TreeNode<T>;
    p->val=value;
    p->left=nullptr;
    p->right=nullptr;
    p->parent=f;
    
    if(!f)          //当f为空指针时，说明root也不存在，此时p为根节点；
        root=p;
    else if(value<f->val)
        f->left=p;
    else if(value>f->val)
        f->right=p;
    return;
}

template<class T> TreeNode<T> * BinarySearchTree<T>::precursor(TreeNode<T> * p){
    if(!p)
        return nullptr;
    if(p->left) //当左子树存在时，取右子树最右侧节点
    {
        TreeNode<T> * r=p->left;
        while(r->right)
            r=r->right;
        return r;
    }
    else //左子树不存在时，往上寻找父亲节点
    {
        TreeNode<T> * f=p->parent;
        TreeNode<T> * n=p;
        while (f&&f->left==n) { //父节点存在，且左子树为本节点，向上寻找；不存在时或者父亲右子树为本节点，停止
            n=f;
            f=f->parent;}
        return f;      //当p为根节点时，f为空，也可以正确返回；
    }
}

template<class T> TreeNode<T> * BinarySearchTree<T>::succeed(TreeNode<T> * p){
    if(!p)
        return nullptr;
    
    if(p->right) //当右子树存在时，取右子树最左侧节点
    {
        TreeNode<T> * l=p->right;
        while(l->left)
            l=l->left;
        return l;
    }
    else //右子树不存在时，往上寻找父亲节点
    {
        TreeNode<T> * f=p->parent;
        TreeNode<T> * n=p;
        while (f&&f->right==n) { //父节点存在，且右子树为本节点，向上寻找；不存在时或者父亲左子树为本节点，停止
                n=f;
                f=f->parent;}
        return f;           //当p为根节点时，f为空，也可以正确返回；
    }
    
}

//用q来代替p， 只将p的父子关系过继给q
template<class T> void BinarySearchTree<T>::transplant(TreeNode<T> * p,TreeNode<T> * q)
{
    if(q)
        q->parent=p->parent;
    
    if(!p->parent)
         root=q;
    else if(p->parent->left==p)
        p->parent->left=q;
    else
        p->parent->right=q;
       
}

template<class T> void BinarySearchTree<T>::deleteVal(T value){
    //先寻找位置
    TreeNode<T> *pos=search(value);
    if(!pos)
        return;
    else
        size--;
    
    //不存在左子树的情况，将右子树替代此节点
    //存在左子树的情况下，寻找后继元素代替此节点；
    if(!pos->left)
    {
        TreeNode<T> *r=pos->right;
        transplant(pos, r);
        delete pos;
    }
    else
    {
        if(!pos->right)
        {
            TreeNode<T> *l=pos->left;
            transplant(pos, l);
            delete pos;
            return;
        }
        TreeNode<T> *suc=succeed(pos); //此后继一定存在，并且无左子树
        //处理suc与原来相邻元素的关系
        TreeNode<T> *suc_r=suc->right;
        transplant(suc, suc_r);
        
        transplant(pos, suc); //用suc代替pos
        suc->left=pos->left;  //处理与pos左节点的关系
        pos->left->parent=suc;
        delete pos;
    }
    
}


template<class T> TreeNode<T> * BinarySearchTree<T>::search(T value){
    if(!root)
        return nullptr;
    TreeNode<T> * p=root;
    while(p)
    {
        if(value==p->val)
            return p;
        else if(value<p->val)
            p=p->left;
        else
            p=p->right;
    }
    return nullptr;
}

template<class T> void BinarySearchTree<T>::layerorder(){
   //构造一个队列；
    TreeNode<T>* queue[size];
    long start=-1,end=-1;
    if(root)
        queue[++end]=root;
    else
        std::cout<<"this tree is empty!"<<std::endl;
    while(start<end)
    {
        TreeNode<T>* p=queue[++start];
        std::cout<<p->val <<" "<<" ";
        if(p->left)
            queue[++end]=p->left;
        if(p->right)
            queue[++end]=p->right;
    }
    return;
}

template<class T> void BinarySearchTree<T>::inorder(){
        
    //构造一个栈；
    TreeNode<T>* stack[size];
    long top=-1;
    if(root)
        stack[++top]=root;
    else
        std::cout<<"this tree is empty!"<<std::endl;
    
    while(top>=0)
    {
        TreeNode<T>* p=stack[top--];
        std::cout<<p->val <<" "<<" ";
        if(p->right)               //需要先遍历左子树，所以右子树先进栈；
            stack[++top]=p->right;
        if(p->left)
            stack[++top]=p->left;
    }
    std::cout<<std::endl;
    return;
   
}


template<class T> void BinarySearchTree<T>::preorder(){
    //思路一,递归寻找后继；这样时间开销较大；
    //思路二，还是构造一个栈，但插入元素的顺序不同
    if(!root){
        std::cout<<"this tree is empty!"<<std::endl;
        return;
    }
    
    TreeNode<T>* stack[size];
    long top=-1;
    TreeNode<T>* p=root;
    
    while(p||top>=0)
    {
        while(p){       //递归将左子树全部入栈
            stack[++top]=p;
            p=p->left;}
        p=stack[top--];   //当处理完一个元素后，就会变成它的右子树； 如果右子树不存在，再处理栈里的元素；
        std::cout<<p->val <<" "<<" ";
        p=p->right;
    }
    std::cout<<std::endl;
    return;
}
template<class T> void BinarySearchTree<T>::postorder(){
    //思路一,递归寻找后继；这样时间开销较大；
    //思路二，还是构造一个栈，但插入元素的顺序不同
    if(!root){
        std::cout<<"this tree is empty!"<<std::endl;
        return;
    }
    
    TreeNode<T>* stack[size];
    long top=-1;
    TreeNode<T>* p=root;
    TreeNode<T>* r=nullptr;
    
    while(p||top>=0)
    {
        if(p){
            stack[++top]=p;
            p=p->left;}
        else{
            p=stack[top]; //取栈顶元素，但是不出栈；
            if(p->right && p->right!=r)   //如果右侧有元素且没有被访问过, 变成右子树
                p=p->right;
            else{
                p=stack[top--]; //右侧不能再访问时，处理此节点并出栈
                std::cout<<p->val<<" ";
                r=p;
                p=nullptr;
            }
        }

    }
    std::cout<<std::endl;
    return;
}

//复制树的函数；
template<class T> TreeNode<T>* BinarySearchTree<T>::copy(TreeNode<T> * p,TreeNode<T> * f)
{
    if(!p)
        return nullptr;
    
    TreeNode<T>* tem=new TreeNode<T>;
    tem->val=p->val;
    tem->left=copy(p->left, tem);
    tem->right=copy(p->right,tem);
    tem->parent=f;
    
    if(!p->parent)
        root=tem;
    else if(p->parent->left==p)
        f->left=tem;
    else
        f->right=tem;
    
    return tem;
}
