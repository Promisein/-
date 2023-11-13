#include <iostream>
#include <list>
#include <vector>
using namespace std;
// template <class T>
// struct adj_List
// {
//     int element; // 存放顶点的第一个信息
//     list<T> l;
// };
// int maxPath = 0;
// int temp_Length = 0;
// void DFS(vector<adj_List<int>> graph, int start, bool *reach)
// {
//     reach[start] = false;
//     list<int>::iterator it = graph[start - 1].l.begin();
//     while (it != graph[start - 1].l.end())
//     {
//         if (reach[*it])
//         {
//             // cout << *it << endl;
//             temp_Length++;
//             if (maxPath < temp_Length)
//             {
//                 maxPath = temp_Length;
//             }
//             DFS(graph, *it, reach);
//         }
//         else
//         {
//             it++;
//         }
//         if (it == graph[start - 1].l.end())
//         {
//             temp_Length--; // 走到头返回上一个顶点
//         }
//     }
// }
void dfs(vector<list<int>> graph, int index, bool *reach, int *v, int length, int *max_length, int *distance)
{
    distance[index] = length;
    //cout << "index " << index << endl; 
    for (list<int>::iterator it = graph[index].begin(); it != graph[index].end(); it++)
    {
        if (reach[*it])
        {
            reach[*it] = false;
            *v = *max_length < length ? *it : *v;
            *max_length = *max_length < length ? length : *max_length;
            // if (*max_length < length)
            // {
            //     *v = *it;
            // }
            // if (*max_length < length)
            // {
            //     *max_length = length;
            // }
            dfs(graph, *it, reach, v, length + 1, max_length, distance);
        }
    }
}
void output(vector<list<int>> graph)
{
    for(int i = 0; i < graph.size(); i++)
    {
        for(auto i : graph[i])
        {
            cout << i << " ";
        }
        cout << endl;
    }
}
int main()
{
    int n;
    cin >> n;
    vector<list<int>> graph;
    bool *reach = new bool[n];
    for (int i = 0; i < n; i++)
    {
        list<int> temp;
        graph.push_back(temp);
    }
    for (int i = 0; i < n - 1; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    //output(graph);
    // 完成领接表构造树

    // 找到最大的两个点
    int *distance1 = new int[n];
    int *distance2 = new int[n];
    int length = 0;
    int v1, v2;
    for (int i = 0; i < n; i++)
    {
        reach[i] = true;
    }
    dfs(graph, 0, reach, &v1, 0, &length, distance1);

    length = 0;
    for (int i = 0; i < n; i++)
    {
        reach[i] = true;
    }
    dfs(graph, v1, reach, &v2, 0, &length, distance1);

    length = 0;
    for (int i = 0; i < n; i++)
    {
        reach[i] = true;
    }
    dfs(graph, v2, reach, &v1, 0, &length, distance2);
    for(int i =0; i < n; i++)
    {
        if(distance1[i] > distance2[i])
        {
            cout << distance1[i] <<" ";
        }
        else
        {
            cout << distance2[i] <<" ";
        }
    }
    cout << endl;
    return 0;
}