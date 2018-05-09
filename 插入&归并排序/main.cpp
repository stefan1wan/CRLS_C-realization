//
//  main.cpp
//  InsertSort&MergeSort
//
//  Created by mov on 2018/5/8.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>
#include <climits>
using namespace std;

void InsertSort(int* a, int l, int r){
    for(int i=l+1; i<=r; i++){
        int key=a[i];
        int j; //保存a[i]
        for(j=i-1; j>=l&&a[j]>key; j--)//从i-1到1循环
                a[j+1]=a[j]; //把本元素向上移
        a[j+1]=key; //j=-1 或者 a[j]<=key
    }
}

void Merge(int *a, int l, int m, int r){
    int n1=m-l+1, n2=r-m;
    int arr[n1+1], brr[n2+1];
    for(int i=l; i<=m; i++)
        arr[i-l]=a[i];
    for(int j=m+1; j<=r; j++)
        brr[j-m-1]=a[j];
    arr[n1]=INT_MAX;
    brr[n2]=INT_MAX;
    
    int i=0,j=0;
    
    for(int k=l; k<=r; k++)
        if(arr[i]<brr[j])
            a[k]=arr[i++];
        else
            a[k]=brr[j++];
    
}
void MergeSort(int* a, int l, int r){
    if(l>=r) return;
    int m=(l+r)/2;
    MergeSort(a, l, m);
    MergeSort(a, m+1, r);
    Merge(a,l,m,r);
}

int main(int argc, const char * argv[]) {
   
    int a[15]={2,34,56,1,-124,-67,98,90,54,123456,-99999,0,666,-233,1};
    MergeSort(a, 0, 14);
    for(int i=0; i<15; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    return 0;
}
