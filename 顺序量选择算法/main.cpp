//
//  main.cpp
//  RandomSelect
//
//  Created by mov on 2018/5/9.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>
#include <cstdlib>
using namespace std;

int RandomPartition(int *a, int l, int r){
    
    if(l==r)
        return l;
    
    srand((unsigned)NULL);
    for(int i=l; i<r; i++)
    {
        int k=rand()%(r-i+1)+i;
        swap(a[k], a[i]);
    }
    
    int i=l, j=l;
    for(; j<r; j++)
        if(a[j]<a[r])  swap(a[i++], a[j]);
    swap(a[i], a[r]);
    return i;
}

int RandomSelect(int *a, int l, int r, int i){
    
    if(l>r || i>r-l+1 || i<=0)
        return -1;
    
    int mid=RandomPartition(a, l, r);
    
    int k= mid-l+1; //mid的排序
    
    if(k == i)
        return a[mid];
    else if(k > i)
        return RandomSelect(a, l, mid-1, i);
    else
        return RandomSelect(a, mid+1, r, i-k);
}

int main() {
    int a[15]={2, 34, 56, 1, 124,67,98,90,54,123456,99999,0,666,233,1};
    int result= RandomSelect(a, 0, 14, 5 );
    cout<<result<<endl;
}
