//
//  BlackRedTree.cpp
//  BlackRedTree
//
//  Created by mov on 12/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//

#include "BlackRedTree.hpp"
#include <iostream>

/* 为了提高效率，主要的函数都采用非递归方式实现 */

//左旋：x为父节点，将其右儿子作为其父节点，旋转到左侧
template<class T> void RBTree<T>::LEFT_ROTATE(TreeNode<T> * x){
    TreeNode<T>* y=x->right;
    y->parent= x->parent;
    if(x->parent==NIL)
        root=y;
    else if(x->parent->right==x)
        x->parent->right=y;
    else x->parent->left=y;
    
    x->right=y->left;
    y->left->parent=x;
    
    y->left=x;
    x->parent=y;
}
//右旋：x为父节点，将其左儿子作为其父节点，旋转到右侧
template<class T> void RBTree<T>::RIGHT_ROTATE(TreeNode<T> * x){
    TreeNode<T>* y=x->left;
    y->parent= x->parent;
    if(x->parent==NIL)
        root=y;
    else if(x->parent->right==x)
        x->parent->right=y;
    else x->parent->left=y;
    
    x->left=y->right;
    y->right->parent=x;
    
    y->right=x;
    x->parent=y;
}


//插入函数
template<class T> void RBTree<T>::insertVal(T value){
    TreeNode<T>* p=root;
    TreeNode<T>* f=NIL;
    
    /* f记录当前节点的父节点，当p为空指针时，停止循环*/
    while(p!=NIL){
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
    p->color=false;
    p->left=NIL;
    p->right=NIL;
    p->parent=f;
    
    if(f==NIL)         //当f为空指针时，说明root也不存在，此时p为根节点；
        root=p;
    else if(value<f->val)
        f->left=p;
    else if(value>f->val)
        f->right=p;
    
    
    RB_INSERT_FIXUP(p);
    return;
}

template<class T>  void  RBTree<T>::RB_INSERT_FIXUP(TreeNode<T> * z){
    
    //先处理边界条件
    if(z->parent==NIL){
        z->color=true;
        return;
    }
    else if(z->parent->parent==NIL)
        return;
    
    while(z->parent->color==false){
        if(z->parent==z->parent->parent->left){//当父亲为爷爷左儿子
            TreeNode<T> * y=z->parent->parent->right; //y为z的叔叔节点
            if(y->color==false){       //CASE 1
                z->parent->parent->color=false;
                z->parent->color=true;
                y->color=true;
                z=z->parent->parent;
                //z变成它爷爷，继续循环
            }else{
                if(z==z->parent->right){ //CASE 2:
                    LEFT_ROTATE(z->parent);
                    z=z->left;
//                    z=z->parent;
                }
                                       //CASE 3
                RIGHT_ROTATE(z->parent->parent);
                z->parent->color=true;
                y->parent->color=false;
            }
        }else{////当父亲为爷爷右儿子
            TreeNode<T> * y=z->parent->parent->left; //y为z的叔叔节点
            if(y->color==false){       //CASE 1
                z->parent->parent->color=false;
                z->parent->color=true;
                y->color=true;
                z=z->parent->parent;
                //z变成它爷爷，继续循环
            }else{
                if(z==z->parent->left){ //CASE 2:
                    RIGHT_ROTATE(z->parent);
//                    z=z->parent;
                    z=z->right;
                }
                //CASE 3
                LEFT_ROTATE(z->parent->parent);
                z->parent->color=true;
                y->parent->color=false;
            }
        }
    }
    root->color=true;
}


//删除节点后，对树的调整；x所代表的树黑高加一，维持性质不变；若x为红色，则x变黑；若x为黑色，进行调整；
template<class T>  void  RBTree<T>::RB_DELETE_FIXUP(TreeNode<T> * x){
    while(x!=root && x->color==true){
        if(x==x->parent->left){//x为父亲节点左儿子
            TreeNode<T>* w=x->parent->right;
            if(w->color==false){ //CASE 1//如果兄弟节点为红色，则旋转，让最终兄弟节点为黑色----->2,3,4
                LEFT_ROTATE(x->parent);
                w->color=true;
                x->parent->color=false;
                w=x->parent->right;//更新w的值
            }
            if(w->left->color==true&& w->right->color==true){//CASE 2--->循环
                w->color=false;
                x=x->parent;
            }
            else{
                if(w->right->color==true){//CASE 3 --->4
                    w->color=false;
                    w->left->color=true;
                    RIGHT_ROTATE(w);
                    w=x->parent->right;
                }
                //CASE 4 --->解决问题
                LEFT_ROTATE(x->parent);
                w->color=x->parent->color;
                x->parent->color=true;
                w->right->color=true;
            }
        }else{//x为父亲节点右儿子
            TreeNode<T>* w=x->parent->left;
            if(w->color==false){ //CASE 1//如果兄弟节点为红色，则旋转，让最终兄弟节点为黑色----->2,3,4
                RIGHT_ROTATE(x->parent);
                w->color=true;
                x->parent->color=false;
                w=x->parent->left;//更新w的值
            }
            if(w->right->color==true&& w->left->color==true){//CASE 2--->循环
                w->color=false;
                x=x->parent;
            }
            else{
                if(w->left->color==true){//CASE 3 --->4
                    w->color=false;
                    w->right->color=true;
                    LEFT_ROTATE(w);
                    w=x->parent->left;
                }
                //CASE 4 --->解决问题
                RIGHT_ROTATE(x->parent);
                w->color=x->parent->color;
                x->parent->color=true;
                w->left->color=true;
            }
        }
        
    }
    x->color=true;
}


//用q来代替p， 只将p的父子关系过继给q
//树移植,删除节点时会用到 
template<class T> void RBTree<T>::transplant(TreeNode<T> * p,TreeNode<T> * q)
{
    q->parent=p->parent;
    
    if(p->parent==NIL)
        root=q;
    else if(p->parent->left==p)
        p->parent->left=q;
    else
        p->parent->right=q;
    
}

//删除
template<class T> void RBTree<T>::deleteVal(T value){
    //先寻找位置
    TreeNode<T> *pos=search(value);
    if(pos==NIL)
        return;
    else size--;
    
    TreeNode<T> *y=pos;   //y代表被删除的节点
    bool y_color=pos->color; //记录被删节点的颜色
    
    TreeNode<T> *x;//x记录节点被删除之后，被删位置的代表树
    //不存在左子树的情况，将右子树替代此节点
    //存在左子树的情况下，寻找后继元素代替此节点；
    if(pos->left==NIL)
    {
        x=pos->right;
        transplant(pos, x);
        x->color=pos->color;
        delete pos;
    
    }
    else if(pos->right==NIL){
            x=pos->left;
            transplant(pos, x);
            x->color=pos->color;
            delete pos;
        }
    else{
        y=succeed(pos);  //此后继一定存在，并且无左子树
        //处理suc与原来相邻元素的关系
        x=y->right;
        transplant(y, x);
        
        transplant(pos, y); //用suc代替pos
        y->color=pos->color;
        y->left=pos->left;  //处理与pos左节点的关系
        pos->left->parent=y;
        
        delete pos;
    }
    if(y_color)
        RB_DELETE_FIXUP(x);
}


//前驱
template<class T> TreeNode<T> * RBTree<T>::precursor(TreeNode<T> * p){
    if(p==NIL)
        return nullptr;
    if(p->left!=NIL) //当左子树存在时，取右子树最右侧节点
    {
        TreeNode<T> * r=p->left;
        while(r->right!=NIL)
            r=r->right;
        return r;
    }
    else //左子树不存在时，往上寻找父亲节点
    {
        TreeNode<T> * f=p->parent;
        TreeNode<T> * n=p;
        while (f!=NIL&&f->left==n) { //父节点存在，且左子树为本节点，向上寻找；不存在时或者父亲右子树为本节点，停止
            n=f;
            f=f->parent;}
        return f;      //当p为根节点时，f为空，也可以正确返回；
    }
}

//后继
template<class T> TreeNode<T> * RBTree<T>::succeed(TreeNode<T> * p){
    if(p==NIL)
        return NIL;
    
    if(p->right!=NIL) //当右子树存在时，取右子树最左侧节点
    {
        TreeNode<T> * l=p->right;
        while(l->left!=NIL)
            l=l->left;
        return l;
    }
    else //右子树不存在时，往上寻找父亲节点
    {
        TreeNode<T> * f=p->parent;
        TreeNode<T> * n=p;
        while (f!=NIL&&f->right==n) { //父节点存在，且右子树为本节点，向上寻找；不存在时或者父亲左子树为本节点，停止
            n=f;
            f=f->parent;}
        return f;           //当p为根节点时，f为空，也可以正确返回；
    }
    
}


template<class T> TreeNode<T> * RBTree<T>::search(T value){
    if(root==NIL)
        return NIL;
    TreeNode<T> * p=root;
    while(p!=NIL)
    {
        if(value==p->val)
            return p;
        else if(value<p->val)
            p=p->left;
        else
            p=p->right;
    }
    return NIL;
}

template<class T> void RBTree<T>::layerorder(){
    //构造一个队列；
    TreeNode<T>* queue[size];
    long start=-1,end=-1;
    if(root!=NIL)
        queue[++end]=root;
    else
        std::cout<<"this tree is empty!"<<std::endl;
    while(start<end)
    {
        TreeNode<T>* p=queue[++start];
        std::cout<<p->val <<" "<<" ";
        if(p->left!=NIL)
            queue[++end]=p->left;
        if(p->right!=NIL)
            queue[++end]=p->right;
    }
    std::cout<<std::endl;
    return;
}

template<class T> void RBTree<T>::inorder(){
    
    //构造一个栈；
    TreeNode<T>* stack[size];
    long top=-1;
    if(root!=NIL)
        stack[++top]=root;
    else
        std::cout<<"this tree is empty!"<<std::endl;
    
    while(top>=0)
    {
        TreeNode<T>* p=stack[top--];
        std::cout<<p->val <<" "<<" ";
        if(p->right!=NIL)               //需要先遍历左子树，所以右子树先进栈；
            stack[++top]=p->right;
        if(p->left!=NIL)
            stack[++top]=p->left;
    }
    std::cout<<std::endl;
    return;
    
}


template<class T> void RBTree<T>::preorder(){
    //思路一,递归寻找后继；这样时间开销较大；
    //思路二，还是构造一个栈，但插入元素的顺序不同
    if(root==NIL){
        std::cout<<"this tree is empty!"<<std::endl;
        return;
    }
    
    TreeNode<T>* stack[size];
    long top=-1;
    TreeNode<T>* p=root;
    
    while(p!=NIL||top>=0)
    {
        while(p!=NIL){     //递归将左子树全部入栈
            stack[++top]=p;
            p=p->left;}
        p=stack[top--];   //当处理完一个元素后，就会变成它的右子树； 如果右子树不存在，再处理栈里的元素；
        std::cout<<p->val <<" "<<" ";
        p=p->right;
    }
    std::cout<<std::endl;
    return;
}
template<class T> void RBTree<T>::postorder(){
    //思路一,递归寻找后继；这样时间开销较大；
    //思路二，还是构造一个栈，但插入元素的顺序不同
    if(root==NIL){
        std::cout<<"this tree is empty!"<<std::endl;
        return;
    }
    
    TreeNode<T>* stack[size];
    long top=-1;
    TreeNode<T>* p=root;
    TreeNode<T>* r=NIL;
    
    while(p!=NIL||top>=0)
    {
        if(p!=NIL){
            stack[++top]=p;
            p=p->left;}
        else{
            p=stack[top]; //取栈顶元素，但是不出栈；
            if(p->right!=NIL && p->right!=r)   //如果右侧有元素且没有被访问过, 变成右子树
                p=p->right;
            else{
                p=stack[top--]; //右侧不能再访问时，处理此节点并出栈
                std::cout<<p->val<<" ";
                r=p;
                p=NIL;
            }
        }
        
    }
    std::cout<<std::endl;
    return;
}

//复制树的函数；
template<class T> TreeNode<T>* RBTree<T>::copy(TreeNode<T> * p,TreeNode<T> * f, const RBTree<T>& C)
{
    if(p==C.NIL)
        return NIL;
    
    TreeNode<T>* tem= new TreeNode<T>;
    tem->val= p->val;
    tem->color=p->color;
    tem->left=copy(p->left, tem, C);
    tem->right=copy(p->right,tem, C);
    tem->parent=f;
    
    if(p->parent==C.NIL)
        root=tem;
    else if(p->parent->left==p)
        f->left=tem;
    else
        f->right=tem;

    return tem;
}
