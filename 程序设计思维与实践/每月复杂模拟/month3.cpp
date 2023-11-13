#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;
struct Mouse
{
    int x;
    int y;
    Mouse()
    {
        x = 1;
        y = 1;
    }
    Mouse(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
    bool operator == (Mouse& mouse)
    {
        if (mouse.x == this->x && mouse.y == this->y)
        {
            return true;
        }
        return false;
    }
};

class Notebook
{
public:
    Notebook()
    {
        string firstLine;
        my_Note.push_back(firstLine);
        my_Mouse.x = 1;
        my_Mouse.y = 1;
        line_number = 1;
    }
    void INSERT(); // 在光标后面进行输入
    void MOVE(); //操作光标移动
    void REMOVE(); // 删除笔记本的内容
    void output(); // 输出记事本内容并且最后输出一个换行符
    void COUNT(); // 字数统计
    void COPY(); // 复制
    void FIND(); // 查找
    void SHIFT();
    void outMouse()
    {
        cout << "x = " << my_Mouse.x << "  y = " << my_Mouse.y << endl;
    }
    bool ifEnd()   // 判断是否位于行尾
    {
        if (my_Mouse.x == my_Note[my_Mouse.y - 1].length() + 1)
        {
            return true;
        }
        return false;
    }
private:
    vector<string> my_Note;
    Mouse my_Mouse;
    Mouse startMouse;
    int line_number = 1; // 记录行数
    bool ifShift = false; // 记录是否处于粘滞状态
    bool ifChoose = false; // 记录是否位于选中状态
    vector<string> pasteboard;   // 粘贴板
    vector<string> selectionBoard; // 选中的临时记录板
        
};

void Notebook::INSERT() // 在光标后面进行输入,应该插入后光标往后一格
{
    string model;
    cin >> model;
    if (model == "Char")
    {
        string temp;
        cin >> temp;
        if (my_Mouse.y > line_number)
        {
            cout << "当前鼠标光标位置错误！" << endl;
        }
        else
        {
            my_Note[my_Mouse.y - 1].insert(my_Mouse.x - 1, temp);
            my_Mouse.x++;
        }
    }
    else
    {
        if (model == "Enter")
        {
            if (ifEnd())
            {
                string temp;
                my_Note.insert(my_Note.begin() + my_Mouse.y, temp);
                my_Mouse.y++;
                my_Mouse.x = 1;
                line_number++;
            }
            else // 说明回车后边有内容
            {
                string temp;
                temp = my_Note[my_Mouse.y - 1].substr(my_Mouse.x - 1, my_Note[my_Mouse.y - 1].length() + 1 - my_Mouse.x);
                my_Note[my_Mouse.y - 1].erase(my_Mouse.x - 1, my_Note[my_Mouse.y - 1].length() + 1 - my_Mouse.x);
                my_Note.insert(my_Note.begin() + my_Mouse.y, temp);
                my_Mouse.y++;
                my_Mouse.x = 1;
                line_number++;
            }
        }
        else
        {
            if (model == "Space")
            {
                string temp = " ";
                if (my_Mouse.y > line_number)
                {
                    cout << "当前鼠标光标位置错误！" << endl;
                }
                else
                {
                    my_Note[my_Mouse.y - 1].insert(my_Mouse.x - 1, temp);
                    my_Mouse.x++;
                }
            }
            else
            {
                if (model == "Paste")
                {
                    if (pasteboard.empty())
                    {
                        return;
                    }
                    else
                    {
                        if (pasteboard.size() == 1)
                        {

                            string temp = pasteboard[0];
                            my_Note[my_Mouse.y - 1].insert(my_Mouse.x - 1, temp);
                            my_Mouse.x += temp.length();
                        }
                        else // 这是有shift的情况
                        {
                            /*
                            string temp_end;
                            temp_end = my_Note[my_Mouse.y - 1].substr(my_Mouse.x - 1, my_Note[my_Mouse.y - 1].length() + 1 - my_Mouse.x); // 获取光标后面的内容
                            my_Note[my_Mouse.y - 1].erase(my_Mouse.x - 1, my_Note[my_Mouse.y - 1].length() + 1 - my_Mouse.x);   // 暂时删除光标后面的内容

                            for (int i = 0; i < pasteboard.size(); i++)
                            {
                                string temp;
                                temp = pasteboard[i];

                                my_Note[my_Mouse.y - 1].insert(my_Mouse.x - 1, temp);
                            }
                            // 更新光标位置
                            int temp_y = my_Mouse.y;
                            my_Mouse.y += pasteboard.size() - 1;
                            if (temp_y == my_Mouse.y) // 说明只插入一行数据
                            {

                            }
                            // 最后在光标后插入临时删除的内容
                            my_Note[my_Mouse.y - 1].insert(my_Mouse.x - 1, temp_end);
                            */
                        }
                    }
                }
            }
        }
    }
}

void Notebook::MOVE()
{
    string model;
    cin >> model;
    if (model =="Home") // 鼠标移动到当前行的开头
    {
        my_Mouse.x = 1;
    }
    if (model == "End") // 鼠标移动到当前行的末尾
    {
        my_Mouse.x = my_Note[my_Mouse.y - 1].length() + 1;
    }
    if (model == "Up")
    {
        if (my_Mouse.y == 1) // 光标位于第一行不进行操作
        {
            return;
        }
        if (my_Note[my_Mouse.y - 2].length() + 1 < my_Mouse.x) // 如果上一行的列数小于当前的光标数
        {
            my_Mouse.x = my_Note[my_Mouse.y - 2].length() + 1;
            my_Mouse.y--;
        }
        else
        {
            my_Mouse.y--;
        }
    }
    if (model == "Down")
    {
        if (my_Mouse.y == line_number)
        {
            return;
        }
        if (my_Note[my_Mouse.y].length() + 1 < my_Mouse.x) // 如果下一行的列数小于当前行的列数
        {
            my_Mouse.x = my_Note[my_Mouse.y].length() + 1;
            my_Mouse.y++;
        }
        else
        {
            my_Mouse.y++;
        }
    }
    if (model == "Left")
    {
        if (my_Mouse.x == 1 && my_Mouse.y == 1) // 位于笔记本开头，不需要任何操作
        {
            return;
        }
        else
        {
            if (my_Mouse.x == 1 && my_Mouse.y != 1) // 光标位于某一行的开头，将光标移动到上一行的末尾
            {
                my_Mouse.y--;
                my_Mouse.x = my_Note[my_Mouse.y - 1].length() + 1;
            }
            else
            {
                my_Mouse.x--;
            }
        }
    }
    if (model == "Right")
    {
        if (my_Mouse.y == line_number && my_Mouse.x == my_Note[line_number - 1].length() + 1) // 位于笔记本末尾，不操作
        {
            return;
        }
        else
        {
            if (my_Mouse.x == my_Note[my_Mouse.y - 1].length() + 1 && my_Mouse.y < line_number) // 光标位于某一行的结尾，移动到下一行的开头
            {
                my_Mouse.y++;
                my_Mouse.x = 1;
            }
            else
            {
                my_Mouse.x++;
            }
        }
    }

    

}

void Notebook::REMOVE()
{
    string model;
    cin >> model;
    if (model == "Del") // 删除光标之后的一个字符
    {
        if (my_Mouse.y == line_number && my_Mouse.x == my_Note[line_number - 1].length() + 1) // 位于笔记本末尾，不操作
        {
            return;
        }
        if (my_Mouse.x == my_Note[my_Mouse.y - 1].length() + 1) // 删除换行符
        {
            string temp = my_Note[my_Mouse.y]; // 存储下一行的数据
            my_Note[my_Mouse.y - 1] += temp;
            my_Note.erase(my_Note.begin() + my_Mouse.y); // 删除下一行的数据
            line_number--;
        }
        else
        {
            my_Note[my_Mouse.y - 1].erase(my_Mouse.x - 1, 1);
        }
    }
    if (model == "Backspace") // 删除光标之前的一个字符
    {
        if (my_Mouse.x == 1 && my_Mouse.y == 1) // 位于笔记本开头，不需要任何操作
        {
            return;
        }
        if (my_Mouse.x == 1) // 说明要删除换行符
        {
            string temp = my_Note[my_Mouse.y - 1];
            my_Mouse.x = my_Note[my_Mouse.y - 2].length() + 1;
            my_Note.erase(my_Note.begin() + my_Mouse.y - 1);
            my_Mouse.y--;
            my_Note[my_Mouse.y - 1] += temp;
            line_number--;
        }
        else
        {
            my_Note[my_Mouse.y - 1].erase(my_Mouse.x - 2, 1);
            my_Mouse.x--;
        }
    }
}

void Notebook::COUNT()
{
    int number = 0;
    if (ifShift)
    {
        for (int i = 0; i < pasteboard.size(); i++)
        {
            for (int j = 0; j < pasteboard[i].length(); j++)
            {
                if (pasteboard[i][j] != ' ')
                {
                    number++;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < my_Note.size(); i++)
        {
            for (int j = 0; j < my_Note[i].length(); j++)
            {
                if (my_Note[i][j] != ' ')
                {
                    number++;
                }
            }
        }
    }
    cout << number << endl;
}

void Notebook::COPY()
{
    pasteboard.clear();
    if (ifShift)
    {

    }
    else  //  复制当前行的内容到粘贴板中
    {
        string temp;
        if (my_Note[my_Mouse.y - 1].empty())
        {
            return;
        }
        temp = my_Note[my_Mouse.y - 1];
        pasteboard.push_back(temp);
    }
}

int countSubstring(const string& str, const string& sub)
{
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != string::npos;
        offset = str.find(sub, offset + 1))
    {
        ++count;
    }
    return count;
}

void Notebook::FIND()
{
    int count_number = 0;
    string temp;
    cin >> temp;
    if (ifShift)
    {
        for (int i = 0; i < this->pasteboard.size(); i++)
        {
            int line_count = countSubstring(pasteboard[i], temp);
            count_number += line_count;
        }
    }
    else
    {
        for (int i = 0; i < my_Note.size(); i++)
        {
            int line_count = countSubstring(my_Note[i], temp);
            count_number += line_count;
        }
    }
    cout << count_number << endl;

}

void Notebook::output()
{
    for (auto i : my_Note)
    {
        cout << i << endl;
    }
    // cout << "Mouse Position: (" << my_Mouse.x << ", " << my_Mouse.y << ")" << endl;
}

void Notebook::SHIFT()
{
    if (ifShift)
    {
        ifShift = false;
        // 从startMouse 到 现在的位置的文本都复制到选中板中
        if (startMouse == my_Mouse)
        {
            return;
        }
        if (startMouse.y == my_Mouse.y)
        {
            if (startMouse.x > my_Mouse.x)
            {
                selectionBoard.push_back(my_Note[my_Mouse.y - 1].substr(my_Mouse.x - 1, startMouse.x - my_Mouse.x));
                //  ababa
            }
            else
            {
                if (startMouse.x < my_Mouse.x)
                {
                    selectionBoard.push_back(my_Note[startMouse.y - 1].substr(startMouse.x - 1, my_Mouse.x - startMouse.x));
                }
            }
        }
        else
        {
            if (startMouse.y > my_Mouse.y)
            {
                selectionBoard.push_back(my_Note[my_Mouse.y - 1].substr(my_Mouse.x - 1, my_Note[my_Mouse.y - 1].length() - my_Mouse.x + 1));
                for (int i = my_Mouse.y; i < startMouse.y - 1; i++)
                {
                    selectionBoard.push_back(my_Note[i]);
                }
                selectionBoard.push_back(my_Note[startMouse.y - 1].substr(0, startMouse.x - 1));
            }
            else
            {
                selectionBoard.push_back(my_Note[startMouse.y - 1].substr(startMouse.x - 1, my_Note[startMouse.y - 1].length() - startMouse.x + 1));
                for (int i = startMouse.y; i < my_Mouse.y; i++)
                {
                    selectionBoard.push_back(my_Note[i]);
                }
                selectionBoard.push_back(my_Note[my_Mouse.y - 1].substr(0, my_Mouse.x - 1));
            }
        }
    }
    else
    {
        startMouse = my_Mouse; // 记录起始的位置
        ifShift = true;
    }
}
int main()
{
    int n;
    cin >> n;
    Notebook Note;
    while (n != 0)
    {
        string opt;
        cin >> opt;
        if (opt == "INSERT")
        {
            Note.INSERT();
        }
        if (opt == "MOVE")
        {
            Note.MOVE();
        }
        if (opt == "PRINT")
        {
            Note.output();
        }
        if (opt == "REMOVE")
        {
            Note.REMOVE();
        }
        if (opt == "SHIFT")
        {
            Note.SHIFT();
        }
        if (opt == "FIND")
        {
            Note.FIND();
        }
        if (opt == "COUNT")
        {
            Note.COUNT();
        }
        if (opt == "COPY")
        {
            Note.COPY();
        }
        if (opt == "MOUSE")
        {
            Note.outMouse();
        }
        n--;
    }
    return 0;
}
/*
100
INSERT Char 7
INSERT Char 8
INSERT Char 9
INSERT Char o
PRINT
MOVE left
INSERT Enter
PRINT
MOVE Left
INSERT p
PRINT
INSERT Char p
PRINT
MOVE Left
INSERT Enter
PRINT
MOUSE
*/