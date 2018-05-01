//
//  main.cpp
//  BlackRedTree
//
//  Created by mov on 12/04/2018.
//  Copyright © 2018 wjp. All rights reserved.
//
#include "BlackRedTree.hpp"
#include "BlackRedTree.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    RBTree<int> a;
    a.insertVal(10);
    a.insertVal(2);
    a.insertVal(6);
    a.insertVal(11);
    
    a.inorder();
    a.layerorder();
    a.preorder();
    
    RBTree<int> b=a;
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
