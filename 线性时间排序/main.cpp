//
//  main.cpp
//  LinearTimeSort
//
//  Created by mov on 2018/5/9.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>

using namespace std;

void CountingSort(int* a, int l, int r, int countingrange){
    int * count= (int *) malloc(sizeof(int) * countingrange);
    memset(count, 0, sizeof(int) * countingrange);
    
    for(int i=l; i<=r; i++)
        count[a[i]]++;
    //用数组b存放a的值
    int b[r-l+1];
    for(int i=0; i<r-l+1; i++){
        b[i]=a[i-l];
    }
    
    //记录每个元素的位置范围
    for(int k=1; k<countingrange; k++)
        count[k] += count[k-1];
    //从后往前遍历，保证是稳定的排序
    //个数先-1 得到位置
    for(int j=r-l; j>=0; j--){
        count[b[j]]-=1;
        int pos = count[b[j]];
        a[pos]= b[j];
    }
}


void CountingSort_ForRadix(int* a, int l, int r, int h,int countingrange){
    int * count= (int *) malloc(sizeof(int) * countingrange);
    memset(count, 0, sizeof(int) * countingrange);
    

    //用数组b存放a的值
    int b[r-l+1];
    int c[r-l+1];
    for(int i=0; i<r-l+1; i++){
        b[i]=a[i-l];
        c[i]=a[i-l];
        int x=h;
        while(x-->0)
            b[i]=b[i]/10;
        b[i]=b[i]%10;
    }
    
    
    for(int i=0; i<r-l+1; i++)
        count[b[i]]++;
    //记录每个元素的位置范围
    for(int k=1; k<countingrange; k++)
        count[k] += count[k-1];
    
    //从后往前遍历，保证是稳定的排序
    //个数先-1 得到位置
    for(int j=r-l; j>=0; j--){
        count[b[j]]-=1;
        int pos = count[b[j]];
        a[pos]= c[j];
    }
}


void RadixSort(int *a, int l, int r,int d){
    for(int i=0; i<d; i++){
        int countingrange=0;
        for(int i=l; i<=r; i++)
            if(a[i]>countingrange)
                countingrange=a[i];
        CountingSort_ForRadix(a, l, r, i, 20);
    }
}


int main() {
    
    int a[15]={2,34,56,1,124,67,98,90,54,123456,99999,0,666,233,1};
    int b[10]={9,8,12,9,3,15,7,1,19,0}; //b的范围是20
    CountingSort(b, 0, 9, 20);
    
    RadixSort(a, 0, 14, 6);
    
    for(int i=0; i<15; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    for(int i=0; i<10; i++){
        cout<<b[i]<<" ";
    }
    cout<<endl;
    
}
