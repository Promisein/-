#include <bits/stdc++.h>
using namespace std;
int *if_no;
int **dangerNode;
int *LASTDATA;
int *num;
vector<pair<int, int>> *myGraph;
queue<int> *nextM;
int n, m, l;
void BuildGraph()
{
    for (int j = 1; j <= n; j++) // 构建图
    {
        int a;
        cin >> a;
        if_no[j] = a;
        int num;
        cin >> num;
        for (int i = 1; i <= num; i++)
        {
            int p, q;
            cin >> p >> q;
            myGraph[j].push_back(make_pair(q, p));
        }
    }
}
void output(int mydata, int nowNode)
{
    if (mydata == 0) // 输出答案
    {
        cout << nowNode << ' ' << "No" << endl;
    }
    else
    {
        cout << nowNode << ' ' << "Yes" << endl;
    }
}
int main()
{

    cin >> n >> m >> l;
    if_no = new int[n + 1]();    // 记录是否为恶意节点
    dangerNode = new int *[n + 1](); // 各点认为的后继节点的不安全次数
    myGraph = new vector<pair<int, int>>[n + 1];
    nextM = new queue<int>[n + 1];
    LASTDATA = new int[n + 1](); // 记录每个节点在一次任务重上次传输的数据
    for (int i = 0; i <= n; i++)
    {
        dangerNode[i] = new int[n + 1]();
    }

    BuildGraph();

    for (int j = 1; j <= n; j++) //
    {
        sort(myGraph[j].begin(), myGraph[j].end(), greater<pair<int, int>>());
    }
    for (int j = 1; j <= n; j++) // 优先级从大到小进入队列
    {
        for (auto it : myGraph[j])
        {
            nextM[j].push(it.second);
        }
    }
    int start, jump, nowNode;
    int *ifchange = new int[n + 1](); // 为0不修改后继 为1降低后继优先度 为2删除后继
    int *ifVIS = new int[n + 1]();    // 记录传输过程中经过点的次数
    num = new int[n + 1]();
    int *ns = new int[n + 1]();
    for (int j = 1; j <= m; j++)
    {
        int mydata = 0; // 初始数据
        cin >> start >> jump;
        nowNode = start;
        int cnt = 0;                 // 环的大小
        for (int i = 0; i <= n; i++) // 初始化
        {
            ifVIS[i] = 0;
            LASTDATA[i] = -1;
            ifchange[i] = 0;
            num[i] = 0;
            ns[i] = 0;
        }
        int node = 0;

        for (int i = 1; i <= jump + 1; i++) // 跳k次或者停止
        {
            if (i == 500)
            {
                node = nowNode;
            }
            if (i > 500 && node == nowNode)
            {
                cnt = i - 500;
                i = jump - ((jump - i) % cnt);
            }
            if (nextM[nowNode].empty() || i == jump + 1) // 若无法继续下传
            {
                if (if_no[nowNode] == 1) // 若为恶意节点
                {
                    mydata++;
                }
                else // 若当前节点不为恶意节点
                {
                    ifVIS[nowNode]++;
                    if (ifVIS[nowNode] >= 2) // 至少第二次到达该点 数据校验
                    {
                        if (mydata != LASTDATA[nowNode]) // 与上次所传数据不同
                        {
                            dangerNode[nowNode][nextM[nowNode].front()]++; // 危险次数加一
                            if (ifchange[nowNode] == 0)
                                ifchange[nowNode] = 1;
                            if (dangerNode[nowNode][nextM[nowNode].front()] >= l) // 如果认为不安全次数大于等于l
                            {
                                ifchange[nowNode] = 2;
                            }
                        }
                    }
                    else
                    {
                        ifVIS[nowNode]--; // 防止与下面代码重复++不安全次数
                    }
                    LASTDATA[nowNode] = mydata;
                }
                break;
            }

            if (if_no[nowNode] == 1) // 若当前节点为恶意节点
            {
                mydata++;
                ifchange[nowNode] = 1; // 更改优先度
                nowNode = nextM[nowNode].front();
            }
            else // 若当前节点不为恶意节点
            {
                ifVIS[nowNode]++;
                if (ifVIS[nowNode] >= 2) // 至少第二次到达该点
                {
                    if (ifVIS[nowNode] == 2)
                        cnt = i - num[nowNode];
                    if (mydata != LASTDATA[nowNode]) // 与上次所传数据不同
                    {
                        dangerNode[nowNode][nextM[nowNode].front()]++;
                        ns[nowNode]++;
                        if (ifchange[nowNode] == 0)
                            ifchange[nowNode] = 1;
                        if (dangerNode[nowNode][nextM[nowNode].front()] >= l) // 如果认为不安全次数大于等于l
                        {
                            ifchange[nowNode] = 2;
                        }
                    }
                }
                else
                {
                    num[nowNode] == i;
                }
                LASTDATA[nowNode] = mydata;
                nowNode = nextM[nowNode].front();
            }
        }
        // 任务结束 修改后继
        for (int i = 1; i <= n; i++)
        {
            if (ifVIS[i] == 1) // 若只经过该节点一次 且有数据流向其后继
            {
                if (ifchange[i] == 0)
                    ifchange[i] = 1;
                dangerNode[i][nextM[i].front()]++;        // 不安全次数加一
                if (dangerNode[i][nextM[i].front()] >= l) // 如果认为不安全次数大于等于l
                {
                    ifchange[i] = 2;
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (ifchange[i] == 1) // 改变不安全后继优先级
            {
                int V1 = nextM[i].front();
                nextM[i].pop();
                nextM[i].push(V1);
            }
            else if (ifchange[i] == 2) // 删除后继节点
            {
                nextM[i].pop();
            }
        }
        output(mydata, nowNode);
    }
}