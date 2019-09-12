#include<bits/stdc++.h>
using namespace std;

int getMin(char *str){
    int i = 0, j = 1, k = 0;
    int len = strlen(str);
    while(i < len && j < len && k < len){
        int tmp =str[(i + k) % len] - str[(j + k) % len];
        if(!tmp) k++;
        else{
            if(tmp > 0) i = i + k + 1;
            else j = j + k + 1;
            if(j == i) ++j;
            k = 0;
        }
    }
    return min(i,j);
}

int getMax(char *str){
    int i = 0,j = 1, k = 0;
    int len = strlen(str);
    while(i < len && j < len && k < len){
        int tmp = str[(i + k) % len] - str[(j + k) % len];
        if(!tmp) k++;
        else{
            if(tmp > 0) j = j + k + 1;
            else i = i + k + 1;
            if(i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}

int main(){
    return 0;
}