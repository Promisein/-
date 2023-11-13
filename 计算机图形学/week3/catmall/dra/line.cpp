#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

struct point_2V
{
    int p_id;
    double x = 0;
    double y = 0;
    int degree = 0; // 这个点的度
    point_2V operator+(const point_2V &p)
    {
        point_2V temp;
        temp.x = this->x + p.x;
        temp.y = this->y + p.y;
        return temp;
    }
    point_2V operator-(const point_2V &p)
    {
        point_2V temp;
        temp.x = this->x - p.x;
        temp.y = this->y - p.y;
        return temp;
    }
};
struct edge
{
    int e_id;               // 边索引
    int from;               // 出发点的索引
    int to;                 // 到达点的索引
    vector<int> face_index; // 这个边包含的面索引
};
struct new_edge //  存储点的边
{
    point_2V from;
    point_2V to;
};
struct face
{
    int f_id;
    vector<int> es; // 属于该面的所有边的索引
    vector<int> vs; // 属于该面的所有点的索引
};

void readObj(string filename, vector<point_2V> &p, vector<edge> &e, vector<face> &f)
{
    ifstream readFile;
    readFile.open(filename, ios::in);
    if (readFile.is_open())
    {
        cout << "文件打开成功！" << endl;
        string str;
        int point_index = 1;
        int edge_index = 1;
        int face_index = 1;
        while (getline(readFile, str))
        {
            if (str.substr(0, 2) == "v ")
            {
                stringstream s(str.substr(2));
                point_2V point;
                s >> point.x >> point.y;
                point.p_id = point_index;
                point_index++;
                p.push_back(point);
            }
            else
            {
                if (str.substr(0, 2) == "e ")
                {
                    stringstream s(str.substr(2));
                    edge temp;
                    s >> temp.from >> temp.to;
                    temp.e_id = edge_index;
                    edge_index++;
                    e.push_back(temp);
                }
                else
                {
                    if (str.substr(0, 2) == "f ")
                    {
                        stringstream s(str.substr(2));
                        int temp_index;
                        face temp_face;
                        while (s >> temp_index)
                        {
                            temp_face.f_id = face_index;
                            temp_face.vs.push_back(temp_index);
                        }
                        f.push_back(temp_face);
                        face_index++;
                    }
                }
            }
            // cout << str << endl;
        }

        // 获取这个面由那些边组成
        vector<face>::iterator it_face = f.begin();
        for (it_face; it_face != f.end(); it_face++)
        {
            vector<edge>::iterator it_edge = e.begin();
            for (it_edge; it_edge != e.end(); it_edge++)
            {
                bool judge1 = false;
                bool judge2 = false;
                for (auto i : it_face->vs)
                {
                    if (i == it_edge->from)
                    {
                        judge1 = true;
                    }
                    if (i == it_edge->to)
                    {
                        judge2 = true;
                    }
                }
                if (judge1 && judge2)
                {
                    int temp_id = it_edge->e_id;
                    it_face->es.push_back(temp_id);
                }
            }
        }

        // 存储边所连的面的信息
        vector<edge>::iterator it_edge = e.begin();
        for (it_edge; it_edge != e.end(); it_edge++)
        {
            vector<face>::iterator it_face = f.begin();
            for (it_face; it_face != f.end(); it_face++) // 对于一个顶点遍历所有的面
            {
                bool judge1 = false;
                bool judge2 = false;
                for (auto z : it_face->vs)
                {
                    if (z == it_edge->from)
                    {
                        judge1 = true;
                    }
                    if (z == it_edge->to)
                    {
                        judge2 = true;
                    }
                }
                if (judge1 && judge2)
                {
                    int temp_id = it_face->f_id;
                    it_edge->face_index.push_back(temp_id);
                }
            }
        }

        // 获取每个点的度degree
        vector<point_2V>::iterator it_point = p.begin();
        for (it_point; it_point != p.end(); it_point++)
        {
            vector<edge>::iterator it_edge = e.begin();
            for (it_edge; it_edge != e.end(); it_edge++)
            {
                if (it_edge->from == it_point->p_id || it_edge->to == it_point->p_id)
                {
                    it_point->degree++;
                }
            }
        }
    }
    else
    {
        cout << "文件打开失败！" << endl;
    }
    readFile.close();
}

vector<point_2V> get_face_points(vector<point_2V> &input_points, vector<edge> &input_edges, vector<face> &input_faces)
{
    vector<point_2V> new_points;
    for (auto i : input_faces)
    {
        point_2V temp;
        temp.x = 0, temp.y = 0;
        for (auto j : i.vs) // j 获得的是对应点的索引
        {
            for (auto p : input_points)
            {
                if (p.p_id == j)
                {
                    temp = p + temp;
                    break;
                }
            } // 获得对应的点
        }
        // cout << temp.x << " " << temp.y << endl;
        temp.x = temp.x / i.vs.size();
        temp.y = temp.y / i.vs.size();
        temp.p_id = i.f_id; // 记录这个面点对应的第几个面（面id）
        new_points.push_back(temp);
    }
    return new_points;
}

vector<point_2V> get_edge_points(vector<point_2V> face_points, vector<point_2V> &input_points, vector<edge> &input_edges, vector<face> &input_faces)
{
    // 计算边的中心点，记为edge_center;
    vector<point_2V> edge_center;
    for (auto i : input_edges)
    {
        point_2V temp;
        temp.x = 0, temp.y = 0;
        for (auto j : input_points)
        {
            if (i.from == j.p_id)
            {
                temp = temp + j;
            }
            if (i.to == j.p_id)
            {
                temp = temp + j;
            }
        }
        temp.x = temp.x / 2;
        temp.y = temp.y / 2;
        temp.p_id = i.e_id; // 记录是哪一个边的中点
        cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
        edge_center.push_back(temp);
    }

    cout << "------------" << endl;

    // 计算面中心点
    vector<point_2V> face_points_center;
    // 对于每一条边的相邻的的面求出face_points_center
    for (auto i : input_edges)
    {
        edge temo_edge_point;
        if (i.face_index.size() == 2)
        {
            point_2V temp1, temp2;
            for (auto j : face_points)
            {
                if (j.p_id == i.face_index[0])
                {
                    temp1 = j;
                }
                if (j.p_id == i.face_index[1])
                {
                    temp2 = j;
                }
            }
            point_2V temp3 = temp1 + temp2;
            temp3.x *= 0.5, temp3.y *= 0.5;
            temp3.p_id = i.e_id; // 点的id记录是哪条边的产生的面中点
            cout << temp3.p_id << " " << temp3.x << " " << temp3.y << endl;
            face_points_center.push_back(temp3);
            // 找见对应的两个面中点求
        }
        if (i.face_index.size() == 1) // 处理边界
        {
            point_2V temp;
            for (auto j : edge_center)
            {
                if (i.e_id == j.p_id)
                {
                    temp = j;
                    temp.p_id = j.p_id;
                    cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
                    face_points_center.push_back(temp);
                }
            }
        }
    }
    cout << "-------------" << endl;
    vector<point_2V> edge_points;
    // 似乎可以直接使用公式直接求出
    for (auto i : edge_center)
    {
        for (auto j : face_points_center)
        {
            point_2V temp;
            if (i.p_id == j.p_id) // 寻找同一个边对应的点
            {
                temp = i + j;
                temp.x *= 0.5, temp.y *= 0.5;
                temp.p_id = j.p_id;
                cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
                edge_points.push_back(temp);
            }
        }
    }
    return edge_points;
}

vector<new_edge> get_edge_faceLines(vector<point_2V> face_points, vector<point_2V> edge_points, vector<face> input_faces)
{
    // face_points 存储着是哪个面的中心点，所以找见对应面的边，再找见对应边的中心点连起来
    vector<new_edge> new_edge1;
    for (auto i : face_points)
    {
        for (auto j : input_faces)
        {
            if (i.p_id == j.f_id) // 找见面点对应的面
            {
                for (auto z : j.es) // 在面的边索引找对应的中点边
                {
                    for (auto x : edge_points)
                    {
                        if (z == x.p_id) // 找见对应面对应的边点
                        {
                            new_edge temp;
                            temp.from = i;
                            temp.to = x;
                            new_edge1.push_back(temp);
                        }
                    }
                }
            }
        }
    }
    return new_edge1;
}

vector<point_2V> update_oldPoints(vector<point_2V> face_points, vector<edge> input_edges, vector<point_2V> input_points, vector<face> input_faces)
{
    // 计算边的中心点，记为edge_center;
    vector<point_2V> edge_center;
    for (auto i : input_edges)
    {
        point_2V temp;
        temp.x = 0, temp.y = 0;
        for (auto j : input_points)
        {
            if (i.from == j.p_id)
            {
                temp = temp + j;
            }
            if (i.to == j.p_id)
            {
                temp = temp + j;
            }
        }
        temp.x = temp.x / 2;
        temp.y = temp.y / 2;
        temp.p_id = i.e_id; // 记录是哪一个边的中点
        // cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
        edge_center.push_back(temp);
    }

    cout << "-----------" << endl;
    vector<point_2V> updated_points;
    for (auto i : input_points)
    {
        if (i.degree == 4) // 非奇异点
        {
            point_2V temp;
            // 获取四个边中心点
            for (auto j : input_edges)
            {
                if (j.from == i.p_id || j.to == i.p_id)
                {
                    for (auto z : edge_center)
                    {
                        if (z.p_id == j.e_id)
                        {
                            temp = temp + z;
                        }
                    }
                }
            }
            temp.x *= 2;
            temp.y *= 2;
            temp.x += i.x * 4;
            temp.y += i.y * 4;

            // 寻找四个面点
            for (auto j : input_faces)
            {
                for (auto z : j.vs)
                {
                    if (z == i.p_id) // 说明这个面包含这个点
                    {
                        for (auto x : face_points)
                        {
                            if (x.p_id == j.f_id)
                            {
                                temp = temp + x;
                            }
                        }
                    }
                }
            }
            temp.x /= 16;
            temp.y /= 16;
            temp.p_id = i.p_id;
            cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
            updated_points.push_back(temp);
        }
        else
        {
            if (i.degree > 4) // 奇异点
            {
                point_2V temp;
                // 获取5个边中心点
                for (auto j : input_edges)
                {
                    if (j.from == i.p_id || j.to == i.p_id)
                    {
                        for (auto z : edge_center)
                        {
                            if (z.p_id == j.e_id)
                            {
                                temp = temp + z;
                            }
                        }
                    }
                }
                temp.x *= 2;
                temp.y *= 2;
                temp.x += i.x * 5;
                temp.y += i.y * 5;

                // 寻找四个面点
                for (auto j : input_faces)
                {
                    for (auto z : j.vs)
                    {
                        if (z == i.p_id) // 说明这个面包含这个点
                        {
                            for (auto x : face_points)
                            {
                                if (x.p_id == j.f_id)
                                {
                                    temp = temp + x;
                                }
                            }
                        }
                    }
                }
                temp.x /= 20;
                temp.y /= 20;
                temp.p_id = i.p_id;
                cout << temp.p_id << " " << temp.x << " " << temp.y << endl;
                updated_points.push_back(temp);
            }
            else // 边界点
            {
                point_2V temp;
                temp = i;
                updated_points.push_back(temp);
            }
        }
    }
    return updated_points;
}

vector<new_edge> get_edge_oldLines(vector<point_2V> edge_points, vector<point_2V> updated_points, vector<edge> input_edges)
{
    cout << "---------" << endl;
    vector<new_edge> new_edge2;
    for (auto i : input_edges) // 对于每个旧边找见对应的点和边点
    {
        for (auto j : updated_points)
        {
            for (auto z : edge_points)
            {
                if ((z.p_id == i.e_id && j.p_id == i.from) || (z.p_id == i.e_id && j.p_id == i.to))
                {
                    new_edge temp;
                    temp.from = z;
                    temp.to = j;
                    cout << z.x << " " << z.y<< endl;
                    cout << j.x << " " << j.y<< endl;
                    new_edge2.push_back(temp);
                }
            }
        }
    }
    return new_edge2;
}


void drow_circle(vector<point_2V> input_points, Mat img)
{
    for(auto i : input_points)
    {
        circle(img, Point((i.x * 200 + 100), (i.y * 200 + 100)), 4, Scalar(0, 0, 0), -1);   // remeber !!!
    }
}
void drow_line(vector<new_edge> input_edge, Mat img)
{
    for(auto i : input_edge)
    {
        line(img, Point(i.from.x * 200 + 100, i.from.y * 200 + 100), Point(i.to.x * 200 + 100, i.to.y * 200 + 100), Scalar(0, 0, 255), 1);
    }
}
int main()
{
	// 设置窗口
    // 注意opencv的坐标系原点在左上角
	Mat img = Mat::zeros(Size(800, 800), CV_8UC3);
	img.setTo(255);              // 设置屏幕为白色

	// 画直线函数
	// line(img, p1, p2, Scalar(0, 0, 255), 1);   // 红色
	// line(img, Point(300, 300), Point(758, 400), Scalar(0, 255, 255), 1); // 黄色

    // 画点 p1
	// circle(img, p1, 3, Scalar(0, 255, 0), -1);
    // 画点 p2
	// circle(img, p2, 3, Scalar(120, 120, 120), -1);
    
	vector<point_2V> p; // 存储点
    vector<edge> e;     // 存储边
    vector<face> f;     // 存储面
    string filename = "/home/cs18/Desktop/catmall/dra/graph.obj";
    readObj(filename, p, e, f); // 读取obj文件
    
    // draw the pionts

    // drow_circle(p, img);
    // for(auto i : e)
    // {
    //     line(img, Point(p[i.from - 1].x * 200 + 100, p[i.from - 1].y * 200 + 100), Point(p[i.to - 1].x * 200 + 100, p[i.to - 1].y * 200 + 100), Scalar(0, 0, 255), 1.0);
    // }

    vector<point_2V> face_points; // 存储面点
    face_points = get_face_points(p, e, f);

    vector<point_2V> edge_points; // 存储边点
    edge_points = get_edge_points(face_points, p, e, f);

    vector<point_2V> updated_points;
    updated_points = update_oldPoints(face_points, e, p, f);

    vector<new_edge> new_edge1; // 表示面点到边点的边
    new_edge1 = get_edge_faceLines(face_points, edge_points, f);

    vector<new_edge> new_edge2; // 表示旧点到边点的边
    new_edge2 = get_edge_oldLines(edge_points, updated_points, e);

    // draw face_points

    drow_circle(face_points, img);
    drow_circle(edge_points, img);
    drow_circle(updated_points, img);
    drow_line(new_edge1, img);
    drow_line(new_edge2, img);

    imshow("画板", img);
	waitKey(0);
	return 0;
}