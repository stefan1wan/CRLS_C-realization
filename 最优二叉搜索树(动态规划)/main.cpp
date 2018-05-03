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

double p[n+1]={0, 0.04,0.06,0.08,0.02,0.10, 0.12,0.14};
double q[n+1]={0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

double e[n+2][n+1]={0}; //不使用0行 1-n+1, 0-n
double w[n+2][n+1]={0}; //不使用0行 1-n+1, 0-n
int root[n][n]={0};

void optimal_bst(){
    for(int i=1;i<=n+1; i++){
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for(int l=1; l<=n; l++){ //l为所有长度的书
        for(int i=1; i<=n-l+1; i++){ //i 为起始位置
            int j=i+l-1;           //j为结束位置
            e[i][j]=DBL_MAX;
            w[i][j]=w[i][j-1]+q[j]+p[j];
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
