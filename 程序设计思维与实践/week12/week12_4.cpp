#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
class program
{
public:
    program(int t, int m)
    {
        memory = m;
        time = t;
    }
    bool operator<(program p)
    {
        if (p.time == time)
        {
            return  memory < p.memory;
        }
        else
        {
            return time < p.time;
        }
    }

    int memory;
    int time;
};

const int maxn = 1e6 + 10;
int n, max_memory = 0;
int score[maxn], tree[maxn];
vector<program> arr;

int lowbit(int x)
{
    return x & (-x);
}

void add(int pos, int k)
{
    for (int i = pos; i <= max_memory +1; i += lowbit(i))
    {
        tree[i] += k;
    }
}

int ask(int pos)
{
    int sum = 0;
    for (int i = pos; i >= 1; i -= lowbit(i))
    {
        sum += tree[i];
    }
    return sum;
}
int main()
{
    memset(score, 0, sizeof(score));
    memset(tree, 0, sizeof(tree));
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m, time;
        cin >> time >> m;
        max_memory = max(m, max_memory);
        program tmep(time, m);
        arr.push_back(tmep);
    }
    sort(arr.begin(), arr.end());
    // for (auto i : arr)
    // {
    //     cout << i.time << " " << i.memory << endl;
    // }
    for (int i = 0; i < n; i++)
    {
        add(arr[i].memory + 1, 1);
        score[ask(arr[i].memory + 1) - 1]++;
    }
    // for (int i = 1; i <= max_memory; i++)
    // {
    //     cout << tree[i] << " ";
    // }
    // cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << score[i] << "\n";
    }
    return 0;
}
// n + nlogn +n(2*log(树状数组的树的高度))