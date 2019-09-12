#include<bits/stdc++.h>
using namespace std;
const int mod = 97;

template <class T>
void output(T elem[], const int n){
    for(int i = 0; i < n; ++i){
        cout << elem[i];
        if(i == n - 1){
            cout << endl;
        } else {
            cout << " ";
        }
    }
}

template <class T>
void BinInsertSort(T r[], const int n){
    T *d = new int[n + 1];
    int left = 0, right = 0, i, j;
    d[0] = r[0];
    for(i = 1; i < n; ++i){
        if(r[i] > d[0]){
            j = right;
            while(j > 0 && r[i] < d[j]){
                d[j + 1] = d[j];
                --j;
            }
            d[j + 1] = r[i];
            right = (right + 1) % n;
        } else {
            if(left == 0){
                d[n - 1] = r[i];
                left = n - 1;
            } else {
                j = left;
                while(j < n && r[i] > d[j]){
                    d[j - 1] = d[j];
                    ++j;
                }
                d[j - 1] = r[i];
                left = --left;
            }
        }
    }
    r[0] = d[left];
    for(i = (left + 1) % n,  j = 1;  j < n;  i = (i + 1) % n, j = j + 1){
        r[j] = d[i];
    }
}

int main(){
    int n;
    cout << "number of elemment: ";
    cin >> n;
    int *elem  = new int[n];
    srand(time(NULL));
    map<int, int>mp;
    for(int i = 0; i < n; ++i){
        elem[i] = rand() % mod;
    }
    cout << "Before sorting: ";
    output(elem, n);
    BinInsertSort (elem, n);
    cout << "After sorting: ";
    output(elem, n);
    return 0;
}