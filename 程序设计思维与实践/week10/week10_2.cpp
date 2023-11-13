#include<iostream>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 1e6 + 10; 
#define _SUCCESS_ 0;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> Graph[maxn];
    int in_degree[maxn];
    priority_queue<int,vector<int>, greater<int>> min_heap;
    vector<int> ans;

    for(int i = 1; i <= n; i++)
    {
        in_degree[i] = 0;
    }
    
    for (size_t i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        Graph[from].push_back(to);
        in_degree[to]++;
    }
    
    for(int i = 1; i <= n; i++)
    {
        if(in_degree[i] == 0)
        {
            min_heap.push(i);
        }
    }
    
    while (!min_heap.empty())
    {
        int id = min_heap.top();
        min_heap.pop();
        ans.push_back(id);
        for(auto i : Graph[id] )
        {
            if(--in_degree[i] == 0)
            {
                min_heap.push(i);
            }
        }       
    }

    for(int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return _SUCCESS_;
}