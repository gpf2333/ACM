#include<bits/stdc++.h>
using namespace std;
const int mod = 97;
const int maxn = 100 + 5;

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
void BubbleSort(T *&elem, int n){
    bool ok = false;
    for(int i = 1; i < n && !ok; ++i){
        ok = true;
        for(int j = 0; j < n- i; ++j){
            if(elem[j] > elem[j + 1]){
                swap(elem[j], elem[j + 1]);
                ok = false;
            }
        }
        if(ok){
            break ;
        }
    }
}

template <class T>
void QucikSort(T *&elem, int low, int high){
    T e = elem[low];
    int i = low, j = high;
    while(i < j){
        while(i < j && elem[j] >= e) --j;
        if(i < j) elem[i++] = elem[j];
        while(i < j && elem[i] <= e) ++i;
        if(i < j) elem[j--] = elem[i];
    }
    elem[i] = e;
    if(low < i - 1) QucikSort(elem, low, i - 1);
    if(i + 1 < high) QucikSort(elem, i + 1, high);
}

template<class T>
void ShellSort(T *&elem, int n){
    int d = n / 2;
    while(d > 0){
        for(int i = d; i < n; ++i){
            int j = i - d;
            T e = elem[i];
            while(j >=0 && e < elem[j]){
                elem[j + d] = elem[j];
                j -= d;
            }
            elem[j + d] = e;
        }
        d /= 2;
    }
}

template<class T>
void FilterDown(T *&elem, const int low, const int high){
    int f = low, i = 2 * low + 1;
    T e = elem[low];
    while(i <= high){
        if(i < high && elem[i] < elem[i + 1]) ++i;
        if(e < elem[i]) {
            elem[f] = elem[i];
            f = i;
            i = 2 * i + 1;
        } else {
            break;
        }
    }
    elem[f] = e;
}

template<class T>
void HeapSort(T *&elem, const int n){
    for(int i = (n - 1) / 2; i >= 0; --i){
        FilterDown(elem, i, n - 1);
    }
    for(int i = n - 1; i > 0; --i){
        swap(elem[0], elem[i]);
        FilterDown(elem, 0, i - 1);
    }
}

template<class T>
void Merge(T *&elem, const int low, const int mid, const int high){
    T *temp = new T[high + 1];
    int i = low, j = mid + 1, k = low;
    while(i <= mid && j <= high){
        if(elem[i] <= elem[j]){
            temp[k++] = elem[i++];
        } else {
            temp[k++] = elem[j++];
        }
    }
    while(i <= mid) temp[k++] = elem[i++];
    while(j <= high) temp[k++] = elem[j++];
    for(int i = low; i <= high; ++i) elem[i] = temp[i];
    delete []temp;
}

template<class T>
void MergeSort(T *&elem, const int n){
    int len = 1;
    while(len < n){
        int i = 0;
        while(i + 2 * len <= n){
            Merge(elem, i, i + len - 1, i + 2 * len - 1);
            i += 2 * len;
        }
        if(i + len < n){
            Merge(elem, i, i + len - 1, n - 1);
        }
        len *= 2;
    }
}

template<class T>
void RecursionMergeSort(T *&elem, const int low, const int high, const int n){
    if(low < high){
        int mid = (low + high) >> 1;
        RecursionMergeSort(elem, low, mid, n);
        RecursionMergeSort(elem, mid + 1, high, n);
        Merge(elem, low, mid, high);
    }
}


int main() {
    int n;
    cout << "Input n: ";
    cin >> n;
    int *elem  = new int[n];
    srand(time(NULL));
    for(int i = 0; i < n; ++i){
        elem[i] = rand() % mod;
    }
    cout << "Before sorting: ";
    output(elem, n);
    // BubbleSort(elem, n);
    // QucikSort(elem, 0, n - 1);
    // ShellSort(elem, n);
    // HeapSort(elem, n);
    // MergeSort(elem, n);
    RecursionMergeSort(elem, 0, n - 1, n);

    cout << "After sorting: ";
    output(elem, n);
    return 0;
}