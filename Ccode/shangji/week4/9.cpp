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
int Partition(T elem[], int l, int r){
    T tmp = elem[l];
    while(l < r){
        while(l < r && elem[r] >= tmp) --r;
        if(l < r) elem[l++] = elem[r];
        while(l < r && elem[l] <= tmp) ++l;
        if(l < r) elem[r--] = elem[l];
    }
    elem[l] = tmp;
    return l;
}

template <class T>
void _QuickSort(T elem[], const int n){
    int l, r, mid;
    stack<int> s;
    s.push(0);
    s.push(n - 1);
    while(!s.empty()){
        r = s.top(); s.pop();
        l = s.top(); s.pop();
        while(r - l > 2){
            mid = Partition(elem, l, r);
            if(r - mid > mid - l){ 
                s.push(mid + 1);  //long subsequence to stack
                s.push(r);
                r = mid - 1;
            } else {
                s.push(l);
                s.push(mid + 1);
                l = mid + 1;
            }
        }
        if(r - l == 1) {
            if(elem[l] > elem[r]) swap(elem[l], elem[r]);
        } else if(r - l == 2){
            if(elem[l] > elem[l + 1]) swap(elem[l], elem[l + 1]);
            if(elem[l] > elem[r]) swap(elem[l], elem[r]);
            if(elem[l + 1] > elem[r]) swap(elem[l + 1], elem[r]);
        }
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
    _QuickSort(elem, n);
    cout << "After sorting: ";
    output(elem, n);
    return 0;
    return 0;
}