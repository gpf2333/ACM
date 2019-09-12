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
void CountSort(T elem[], const int n){
    int *cnt = new int[n + 1];
    for(int i = 0; i < n; ++i) cnt[i] = 0;
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(elem[j] < elem[i]) ++cnt[i];
            else ++cnt[j];
        }
    }
    output(cnt, n);
    for(int i = 0;  i < n; ){
        if(cnt[i] < i){
            swap(elem[i], elem[cnt[i]]);
            swap(cnt[i], cnt[cnt[i]]);
        } else {
            ++i;
        }
        //output(elem, n);
    }
    output(elem, n);
}
int main(){
    int n;
    cout << "number of elemment: ";
    cin >> n;
    int *elem  = new int[n];
    srand(time(NULL));
    map<int, int>mp;
    for(int i = 0; i < n; ++i){
        int x = rand() % mod;
        if(mp[x] == 0) {
            mp[x] == 1;
            elem[i] = x;
        } else{
            --i;
        }
    }
    cout << "Before sorting: ";
    output(elem, n);
    CountSort(elem, n);
    cout << "After sorting: ";
    output(elem, n);
    return 0;
}