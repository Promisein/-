#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 2e6 + 100;
typedef long long ll;

ll n, p;
ll last_a = 0;
ll d[maxn << 1], a[maxn];

void build(int x, int l, int r)
{
    if (l == r)
    {
        d[x] == a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);         // left
    build(x * 2 + 1, mid + 1, r); // right

    // 回溯
    d[x] = max(d[x * 2], d[x * 2 + 1]);
}

// 在pos增加v
void update(ll pos, ll val, int x, int l, int r)
{
    if (l == r)
    {
        d[x] += val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
    {
        update(pos, val, x * 2, l, mid);
    }
    else
    {
        update(pos, val, x * 2 + 1, mid + 1, r);
    }

    // 回溯，当前孩子更新，当前结点也要更新
    d[x] = max(d[x * 2], d[x * 2 + 1]);
}

// 区间查询[p1, p2]
ll ask(int x, int l, int r, ll p1, ll p2)
{
    // 如果是当前区间，直接返回
    if (p1 == l && p2 == r)
    {
        return d[x];
    }
    int mid = (l + r) / 2;
    // 查询区间位于左边
    if (p2 <= mid)
    {
        return ask(x * 2, l, mid, p1, p2);
    }
    else
    {
        // 位于右边
        if (p1 > mid)
        {
            return ask(x * 2 + 1, mid + 1, r, p1, p2);
        }
        else // 要查询的区间分布在左右两边，分别计算，合并后作为答案
        {
            ll lch_val = ask(x * 2, l, mid, p1, mid);
            ll rch_val = ask(x * 2 + 1, mid + 1, r, mid + 1, p2);
            return max(lch_val, rch_val);
        }
    }
}

int main()
{
    memset(a, 0, sizeof(a));
    memset(d, 0, sizeof(d));
    cin >> n >> p;
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == 'Q') // 顾客进行了点菜
        {
            int L; // 该顾客的手机屏幕可以显示L个菜品;
            cin >> L;
            int right = pos;
            int left = max(pos - L + 1, 1);
            last_a = ask(1, 1, n, left, right);
            cout << last_a << endl;
        }
        else
        {
            ll t;
            cin >> t;
            t = (t + last_a) % p;
            pos++;
            update(pos, t, 1, 1, n); // 在pos 增加喜爱度 t, 区间为 1 - m
        }
    }
    return 0;
}