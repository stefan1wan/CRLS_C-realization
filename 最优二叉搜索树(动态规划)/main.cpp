//
//  main.cpp
//  OptimalBinarySearchTree
//
//  Created by mov on 2018/5/3.
//  Copyright © 2018 wjp. All rights reserved.
//

#include <iostream>
#include <climits>
#include <cfloat>
#include <iomanip>

using namespace std;
const int n=7;

double p[n+1]={0, 0.04,0.06,0.08,0.02,0.10, 0.12,0.14}; //1-n //访问到每个节点的频率，第一个元素为凑数
double q[n+1]={0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};//0-n //在每个空中，找不到的频率

double e[n+2][n+1]={0}; //不使用0行 1-n+1, 0-n  //产生的某棵树的最小权重
double w[n+2][n+1]={0}; //不使用0行 1-n+1, 0-n //在下层节点上生成树多余的开销
//e,w为对角阵n+1只对应n的情况，代表一个q值

int root[n+1][n+1]={0}; //1-n, 1-n

void optimal_bst(){
    //初始化e,w （线段长度为0的情况下）
    for(int i=1;i<=n+1; i++){
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    
    for(int l=1; l<=n; l++){ //l为所有长度的树
        for(int i=1; i<=n-l+1; i++){ //i 为起始位置
            int j=i+l-1;           //j为结束位置
    /*   先遍历每个长度，再遍历此长度的所有线段  */
            e[i][j]=DBL_MAX;
            w[i][j]=w[i][j-1]+q[j]+p[j];
    /*遍历此线段中所有可以当做根的点*/
            for(int r=i; r<=j; r++){
                double t= e[i][r-1]+ e[r+1][j]+ w[i][j];
                if(t<e[i][j]){
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
        }
    }
}


int main() {
    optimal_bst();
    
    cout.setf(ios::fixed,ios::floatfield);
    for(int i=1; i<=n+1; i++){
        for(int j=0; j<=n; j++)
            cout<<e[i][j]<<setprecision(2)<<" ";
        cout<<endl;
    }
    
    cout<<endl;
    for(int i=1; i<=n+1; i++){
        for(int j=0; j<=n; j++)
            cout<<w[i][j]<<setprecision(2)<<" ";
        cout<<endl;
    }
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            cout<<root[i][j]<<setprecision(2)<<" ";
        cout<<endl;
    }
    
    return 0;
}
