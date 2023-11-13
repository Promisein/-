#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
const long long INF = 1e18;
struct file
{
    bool isDir;       // 是否为目录文件
    long long LD, LR; // 文件配额，分别为目录配额和后代配额
    long long SD, SR; // 表示已用配额
    map<string, file> children;
    long long fileSize;

    file()
    {
        isDir = true;
        LD = LR = INF;
        SD = SR = 0;
        fileSize = 0;
    }
};

file root; // 表示根目录

// Support Vector Machine

vector<string> split(string path)
{
    stringstream ss(path);
    string fileName;
    vector<string> fileNames;
    while (getline(ss, fileName, '/'))
    {
        fileNames.push_back(fileName);
    }
    return fileNames;
}

vector<file *> findNodes(const vector<string> &fileNames)
{
    vector<file *> fileNodes;
    fileNodes.push_back(&root);
    for (int i = 1; i < fileNames.size(); i++)
    {
        if (!fileNodes.back()->isDir)
        {
            return fileNodes;
        }
        if (fileNodes.back()->children.count(fileNames[i]) == 0)
        {
            return fileNodes;
        }
        fileNodes.push_back(&fileNodes.back()->children[fileNames[i]]);
    }
    return fileNodes;
}
bool CreatFile()
{
    string path;
    long long fileSize;
    cin >> path >> fileSize;
    // 解析文件目录
    vector<string> fileNames = split(path);

    // 找出对应的存储单元
    vector<file *> fileNodes = findNodes(fileNames);

    long long increaseSize;
    if (fileNodes.size() == fileNames.size())
    {
        if (fileNodes.back()->isDir)
        {
            return false;
        }
        increaseSize = fileSize - fileNodes.back()->fileSize; // 普通文件替换普通文件
    }
    else
    {
        if (!fileNodes.back()->isDir)
        { // 不能在普通文件下创建目录
            return false;
        }
        increaseSize = fileSize;
    }

    // 检查子节点的配额是否满足
    for (int i = 0; i < fileNodes.size() && i + 1 < fileNames.size(); i++)
    {
        if (fileNodes[i]->SR + increaseSize > fileNodes[i]->LR)
        {
            return false;
        }

        // 判断当前父节点的子节点配额是否满足
        if (i == fileNames.size() - 2 && fileNodes[i]->SD + increaseSize > fileNodes[i]->LD)
        {
            return false;
        }
    }

    // 说明配额满足
    for (int i = fileNodes.size(); i < fileNames.size(); i++)
    {
        fileNodes.push_back(&fileNodes.back()->children[fileNames[i]]);
    }
    // 创建的最后一个文件应该为普通文件
    fileNodes.back()->isDir = false;
    fileNodes.back()->fileSize = fileSize;

    // 修改当前路径上的所有结点的已经配额的值的大小
    for (auto nodes : fileNodes)
    {
        nodes->SR += increaseSize;
    }

    // 对于父节点要更改目录配额
    fileNodes[fileNodes.size() - 2]->SD += increaseSize;
    return true;
}

// 删除文件
bool remove()
{
    string path;
    cin >> path;
    // 解析文件目录
    vector<string> fileNames = split(path);

    // 找出对应的存储单元
    vector<file *> fileNodes = findNodes(fileNames);
    if (fileNodes.size() == fileNames.size())
    {
        if (fileNodes.back()->isDir)
        {
            for (int i = 0; i + 1 < fileNodes.size(); i++)
            {
                fileNodes[i]->SR -= fileNodes.back()->SR;
            }
            fileNodes[fileNodes.size() - 2]->children.erase(fileNames.back());
        }
        else
        {
            for (int i = 0; i + 1 < fileNodes.size(); i++)
            {
                fileNodes[i]->SR -= fileNodes.back()->SR;
            }
            fileNodes[fileNodes.size() - 2]->SD -= fileNodes.back()->fileSize;
            fileNodes[fileNodes.size() - 2]->children.erase(fileNames.back());
        }
    }
    return true;
}

// 文件配额
bool quota()
{
    string path;
    long long LD, LR;
    cin >> path >> LD >> LR;
    if (LD == 0)
    {
        LD = INF;
    }
    if (LR == 0)
    {
        LR = INF;
    }
    // 解析文件目录
    vector<string> fileNames = split(path);

    // 找出对应的存储单元
    vector<file *> fileNodes = findNodes(fileNames);
    if (fileNodes.size() == fileNames.size())
    {
        if (!fileNodes.back()->isDir)
        {
            return false;
        }
        if (fileNodes.back()->SD > LD || fileNodes.back()->SR > LR)
        {
            return false;
        }
        fileNodes.back()->LD = LD;
        fileNodes.back()->LR = LR;
        return true;
    }
    else
    {
        return false;
    }
    
}

int main()
{
    int T;
    cin >> T;
    while (T != 0)
    {
        string op;
        cin >> op;
        bool flag;
        if (op == "C")
        {
            flag = CreatFile();
        }
        if (op == "R")
        {
            flag = remove();
        }
        if (op == "Q")
        {
            flag = quota();
        }
        if (flag)
        {
            cout << "Y " << endl;
        }
        else
        {
            cout << "N" << endl;
        }
        T--;
    }
    return 0;
}