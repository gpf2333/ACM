#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T, int M>
struct Mat
{
    T v[M][M];
    Mat() { std::memset(v, 0, sizeof v); }
    void eye()
    {
        for (int i = 0; i < M; i++) v[i][i] = 1;
    }
    T* operator[](int x) { return v[x]; }
    const T* operator[](int x) const { return v[x]; }
    Mat operator*(const Mat& B)
    {
        const Mat& A = *this;
        Mat ret;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    (ret[i][j] += A[i][k] * B[k][j]) %= p;
        return ret;
    }
    Mat pow(ll n) const
    {
        Mat A = *this, ret;
        ret.eye();
        for (; n; n >>= 1, A = A * A)
            if (n & 1) ret = ret * A;
        return ret;
    }
    Mat operator+(const Mat& B)
    {
        const Mat& A = *this;
        Mat ret;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                ret[i][j] = (A[i][j] + B[i][j]) % p;
        return ret;
    }
};
 
typedef long long ll;
using mat = Mat<ll, 2>;

int main(){
    return 0;
}