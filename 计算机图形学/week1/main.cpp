#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

using namespace std;
struct myPoint
{
    float x;
    float y;
};

//get a triangle area
float get_area(float a1, float a2, float a3,float b1, float b2, float b3)
{
    return 0.5 * abs(a1*b2 - a1*b3 + a2*b3 - a2*b1 + a3*b1 - a3*b2);
}

// the second solution
void function2()
{
    myPoint a, b, c;
    cout << "Please input three points  to construct this triangle:" << endl;
    cout << "First point:" << " ";
    cin >> a.x >> a.y;
    cout << "Second point:" << " ";
    cin >> b.x >> b.y;
    cout << "Three point:" << " ";
    cin >> c.x >> c.y;
    for(int i = 0; i < 10; i++)
    {
        myPoint judge;
        cout << "The point to be judged:"<< endl;
        cin >> judge.x >> judge.y;
    }
    
}

//the first solution
void function1()
{
    //judge a point if included in a triangle

    //input three points  to construct this triangle
    float a1, a2, a3;
    float b1, b2, b3;
    cout << "Please input three points  to construct this triangle:" << endl;
    cout << "First point:" << " ";
    cin >> a1 >> b1;
    cout << "Second point:" << " ";
    cin >> a2 >> b2;
    cout << "Three point:" << " ";
    cin >> a3 >> b3;
    for(int i = 0; i < 10; i++)
    {
        cout << "The point to be judged:"<< endl;
        float x,y;
        cin >> x >> y;
        float area = get_area(a1, a2, a3, b1, b2, b3);
        // cout << area << endl;
        float area1 = get_area(x, a2, a3, y, b2, b3);
        float area2 = get_area(a1, x, a3, b1, y, b3);
        float area3 = get_area(a1, a2, x, b1, b2, y);
        if(area == (area1 + area2 + area3))
        {
            cout << "the point (" << x << ", " << y << ") is in the triangle!" << endl;
        }
        else
        {
            cout << "the point (" << x << ", " << y << ") is **NOT** in the triangle!" << endl;
        }
        cout << "-----------------" << endl;
    }
}
int main()
{
    //function2();
    function1();
    return 0;
}