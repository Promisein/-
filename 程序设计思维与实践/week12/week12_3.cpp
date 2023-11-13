#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 1e6 + 10;
long long arr[maxn];
int n, q;

long long lowbit(long long x)
{
    return x & (-x);
}
void add(int index, int x)
{
    for (int i = index; i <= n; i += lowbit(i))
    {
        arr[i] += x;
    }
}

long long ask(int pos)
{
    long long sum = 0;
    for (int i = pos; i >= 1; i -= lowbit(i))
    {
        sum += arr[i];
    }
    return sum;
}
void output()
{
    for(int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";

    }
    cout << endl;
}
int main()
{

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        arr[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        long long temp;
        cin >> temp;

        add(i, temp);
    }

    while (q != 0)
    {
        // output();
        int op;
        cin >> op;
        if (op == 1) // arr[index] += x;
        {
            int index, x;
            cin >> index >> x;
            add(index, x);
        }
        else // arr[l] + ... + arr[r]
        {
            int r, l;
            cin >> l >> r;
            cout << ask(r) - ask(l - 1) << endl;
        }
        q--;
    }
    return 0;
}
