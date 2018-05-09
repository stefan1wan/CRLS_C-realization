//
//  main.cpp
//  QuickSort
//
//  Created by mov on 2018/5/9.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>

using namespace std;

int Partition(int *a, int l, int r){
    //将最后一个元素作为枢轴量
    int i=l, j=l;
    for(; j<r; j++){
        if(a[j]<a[r])
            swap(a[i++], a[j]);
    }
    swap(a[r], a[i]);
    return i;
}
void QuickSort(int* a, int l, int r){

    if(l>=r) return;
    int mid= Partition(a, l, r);
    QuickSort(a, l, mid-1);
    QuickSort(a, mid+1, r);
    
}

int main() {
    int a[15]={2,34,56,1,-124,-67,98,90,54,123456,-99999,0,666,-233,1};
    QuickSort(a, 0, 14);
    for(int i=0; i<15; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
}
