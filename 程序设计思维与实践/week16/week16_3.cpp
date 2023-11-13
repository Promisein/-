/*
 * 矩阵快速幂求斐波那契数列
 */
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 2;
long long p;
int T;
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
Matrix quick_pow(Matrix a, int x)
{
    Matrix ret;
    ret.x[0][1] = ret.x[1][0] = 0;
    ret.x[0][0] = ret.x[1][1] = 1;
    while (x)
    {
        if (x & 1)
            ret = ret * a;
        a = a * a;
        x >>= 1;
    }
    return ret;
}
ll Fibonacci(ll n, ll p)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    Matrix left;

    left.x[0][0] = left.x[0][1] = left.x[1][0] = 1;
    Matrix res = quick_pow(left, n - 2);
    return (res.x[0][0] + res.x[0][1]) % p;
}
int main()
{
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        ll num;
        cin >> num >> p;
        cout << Fibonacci(num, p) << endl;
    }

    return 0;
}