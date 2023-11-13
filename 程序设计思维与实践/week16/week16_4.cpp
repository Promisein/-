#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 3;
long long p;
struct Matrix
{
    long long x[N][N];
    Matrix operator*(const Matrix &t) const
    {
        Matrix ret;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                ret.x[i][j] = 0;
                for (int k = 0; k < N; k++)
                {
                    ret.x[i][j] += x[i][k] * t.x[k][j] % p;
                    ret.x[i][j] %= p;
                }
            }
        }
        return ret;
    }
    Matrix() { memset(x, 0, sizeof x); }
    Matrix(const Matrix &t) { memcpy(x, t.x, sizeof x); }
};

Matrix quick_pow(Matrix a, ll x)
{
    Matrix ret;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                ret.x[i][j] = 1;
            }
            else
            {
                ret.x[i][j] = 0;
            }
        }
    }
    while (x)
    {
        if (x & 1)
        {
            ret = ret * a;
        }
        a = a * a;
        x >>= 1;
    }
    return ret;
}

void Solution(ll num)
{
    Matrix m1, res;
    m1.x[0][0] = 1;
    m1.x[0][1] = 0;
    m1.x[0][2] = 1;
    m1.x[1][0] = 0;
    m1.x[1][1] = 1;
    m1.x[1][2] = 1;
    m1.x[2][0] = 2;
    m1.x[2][1] = 2;
    m1.x[2][2] = 1;
    res = quick_pow(m1, num - 1);
    cout << (res.x[0][0] % p + (res.x[0][2] * 2) % p) % p << endl;
}
int main()
{
    p = 998244353; 
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        ll num;
        cin >> num;
        Solution(num);
    }
}