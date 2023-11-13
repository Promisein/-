#include <iostream>
using namespace std;
int n, m;
int *f; 

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
// int find(int x)
// {
//     int root = x;
//     while (root != f[root])
//     {
//         root = f[root]; // 找到根
//     }
//     // 压缩路径 所有的子节点都指向根
//     // 这里是吧所有的结点都指向最终的根节点，不用一直父亲结点判断完成后，又一次进行判断
//     while (x != root)
//     {
//         int temp = f[x];
//         f[x] = root;
//         x = temp;
//     }
//     return root;
// }
// void join(int x, int y)
// {
//     f[find(y)] = find(x);  // 将y加入到x中
// }
int main()
{
    cin >> n >> m;
    f = new int[n + 1];
    for (int i = 0; i < n; i++)
    {
        f[i] = i;
    }
    int needPath = n - 1;
    for (int i = 0; i < m; i++)
    {
        
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        if (find(from) != find(to))
        {
            f[f[from]] = f[to];
            needPath--;
        }
        cout << needPath << endl;
    }
    return 0;
}