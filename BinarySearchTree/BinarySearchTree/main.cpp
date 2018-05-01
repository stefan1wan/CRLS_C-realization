//
//  main.cpp
//  BinarySearchTree
//
//  Created by mov on 11/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//
/*
 注意，使用模板的话，必须将声明和实现都放在头文件中，不然找不到函数的实现会报错；
 或者下策是，在需要用的文件中包含cpp文件；
 */

#include <iostream>
#include "BinarySearchTree.hpp"
#include "BinarySearchTree.cpp"

using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    BinarySearchTree<int> a;
    a.insertVal(10);
    a.insertVal(2);
    a.insertVal(6);
    a.insertVal(11);
    
//    a.inorder();
//    a.layerorder();
    a.preorder();
    
    BinarySearchTree<int> b=a;
    b.preorder();
    b.postorder();
    
    a.deleteVal(11);
    a.deleteVal(120);
    a.deleteVal(2);
    a.deleteVal(10);
    a.deleteVal(6);
    
    cout<<endl;
    
    a.insertVal(999);
    a.deleteVal(999);
    a.insertVal(3);
    a.inorder();
    a.preorder();
    cout<<a.search(3)<<endl;
    
    return 0;
}
