//
//  main.cpp
//  Select&HeapSort
//
//  Created by mov on 2018/5/8.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>
using namespace std;

void SelectSort(int* a, int l, int r){
    for(int i=l; i<r; i++){
        int min_v=a[i];
        int ind= i;
        
        int j;
        for(j=i+1; j<=r; j++)
            if(a[j]<min_v){
                min_v=a[j];
                ind=j;
            }
        swap(a[ind], a[i]);
    }
}

//上移是插入新元素用的，堆排序中用不到此操作
void fix_up(int *a, int val, int l);

void fix_down(int* a, int val, int r){
    if(2*val+1> r)//无叶子节点
        return;
    if(2*val+2 >r){ //只有左侧叶子节点
        if(a[val]<a[2*val+1])
            swap(a[val], a[2*val+1]);
        return;
        }
    
    int j=val;
    int max_v=a[val];
    if(a[2*val+1]> max_v){
        j=2*val+1;
        max_v=a[2*val+1];
    }
    if(a[2*val+2]> max_v){
        j=2*val+2;
    }
    
    if(j!=val){
        swap(a[j],a[val]);
        fix_down(a,j,r);
    }
}
//堆从0开始，故左2*i+1; 右 2*i+2;
void HeapSort(int* a, int l, int r){
    //建最大堆, 每次把最大元素移到后面
    int mid=(l+r)/2;
    for(int i=mid; i>=l; i--)
        fix_down(a,i,r);
    //
    for(int i=r; i>l; i--){
        swap(a[i], a[l]); //栈顶元素移到i的位置
        fix_down(a, l, i-1);
    }
    
}
int main(int argc, const char * argv[]) {
    int a[15]={2,34,56,1,-124,-67,98,90,54,123456,-99999,0,666,-233,1};
    HeapSort(a, 0, 14);
    for(int i=0; i<15; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
}
