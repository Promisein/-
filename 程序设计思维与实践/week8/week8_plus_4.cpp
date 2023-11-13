#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
string result;
vector<int> target_top;
vector<int> target_end;
class Cube
{
public:
    Cube()
    {
        for (int i = 0; i < 4; i++)
        {
            top.push_back(i + 1);
            end.push_back(8 - i);
        }
        step = 0;
    }
    Cube(vector<int> ntop, vector<int> nend, int nstep)
    {
        top = ntop;
        end = nend;
        step = nstep;
    }
    Cube(const Cube &c) // 复制构造函数
    {
        top = c.top;
        end = c.end;
        step = c.step;
        path = c.path;
    }

    void A() // 切换上下行
    {
        vector<int> mid = top; // 这里应该可能是浅拷贝
        top = end;
        end = mid;
    }
    void B() // 魔方的最后一列提到最前头
    {
        int end_top = top[3];
        int end_end = end[3];
        vector<int> temp1(top);
        vector<int> temp2(end);
        for (int i = 1; i < 4; i++)
        {
            top[i] = temp1[i - 1];
            end[i] = temp2[i - 1];
        }
        top[0] = end_top;
        end[0] = end_end;
    }
    void C() // 中心顺时针旋转90度
    {
        int temp1, temp2, temp3, temp4;
        temp1 = top[1];
        temp2 = top[2];
        temp3 = end[2];
        temp4 = end[1];
        top[1] = temp4;
        top[2] = temp1;
        end[2] = temp2;
        end[1] = temp3;
    }

    void output()
    {
        for (int i = 0; i < 4; i++)
        {
            cout << top[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << end[i] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
    }

    bool check()
    {
        for (int i = 0; i < 4; i++)
        {
            if (top[i] != target_top[i])
            {
                return false;
            }
            if (end[i] != target_end[i])
            {
                return false;
            }
        }
        return true;
    }

    // bool operator<(Cube &c)
    // {
    //     if (this->transform() < transform())
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    int transform()
    {
        int sum1 = top[0] + 10 * top[1] + 100 * top[2] + 1000 * top[3];
        int sum2 = end[0] * 10000 + end[1] * 100000 + end[2] * 1000000 + end[3] * 10000000;
        return sum1 + sum2;
    }

    vector<int> top;
    vector<int> end;
    int step;
    string path;
};
map<int, int> mp; // 记录是否来过这个状态，用map的性能可能比较快

int bfs(Cube c)
{
    queue<Cube> q;
    q.push(c); // 初始数字入队
    mp[c.transform()] = 1;
    if (c.check())
    {
        // cout << c.path << endl;
        return c.step;
    }
    while (!q.empty())
    {
        Cube now(q.front());
        if (now.check())
        {
            result = now.path;
            // cout << now.path << endl;
            return now.step;
        }
        q.pop();
        for (int i = 0; i < 3; i++) // 分别遍历三种操作
        {
            Cube temp(now);
            if (i == 0)
            {
                temp.A();
                if (mp[temp.transform()] == 0) // 判断这种状态是否来过
                {
                    // temp.output();
                    mp[temp.transform()] = 1;
                    temp.step++;
                    temp.path = temp.path + "A";
                    q.push(temp);
                }
            }
            if (i == 1)
            {
                temp.B();
                if (mp[temp.transform()] == 0) // 判断这种状态是否来过
                {
                    // temp.output();
                    mp[temp.transform()] = 1;
                    temp.step++;
                    temp.path = temp.path + "B";
                    q.push(temp);
                }
            }
            if (i == 2)
            {
                temp.C();
                if (mp[temp.transform()] == 0) // 判断这种状态是否来过
                {
                    // temp.output();
                    mp[temp.transform()] = 1;
                    temp.step++;
                    temp.path = temp.path + "C";
                    q.push(temp);
                }
            }
        }
    }
    return -1;
}
int main()
{
    vector<int> top;
    vector<int> end;
    for (int i = 0; i < 4; i++)
    {
        int temp;
        cin >> temp;
        target_top.push_back(temp);
        top.push_back(i + 1);
        end.push_back(8 - i);
    }
    int temp_end[4];
    for (int i = 0; i < 4; i++)
    {
        cin >> temp_end[i];
    }
    for (int i = 0; i < 4; i++)
    {
        target_end.push_back(temp_end[3 - i]);
    }

    Cube c(top, end, 0);
    cout << bfs(c) << endl;
    cout << result << endl;
    // result = "BCABCCB";
    // for (int i = 0; i < result.size(); i++)
    // {
    //     if (result[i] == 'A')
    //     {
    //         c.A();
    //     }
    //     if (result[i] == 'B')
    //     {
    //         c.B();
    //     }
    //     if (result[i] == 'C')
    //     {
    //         c.C();
    //     }
    //     c.output();
    // }
    return 0;
}