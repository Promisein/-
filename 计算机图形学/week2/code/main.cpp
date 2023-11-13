#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<fstream>
using namespace std;
std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    //if only have two points
    if(control_points.size() == 2)
    {
        return control_points[0] * (1 - t) + t * control_points[1];
    }
    std::vector<cv::Point2f> control_points_temp;    //set temp point
    for(int i = 0; i < control_points.size() - 1; i++)
    {
        control_points_temp.push_back(control_points[i] * (1 - t) + t * control_points[i + 1]);
    }
    return recursive_bezier(control_points_temp, t);

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for(double t = 0; t <= 1; t += 0.001)
    {
        auto point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255;
    }

}
// void simple_Drow(const std::vector<cv::Point2f> &points, cv::Mat &window)
// {
// //    auto &p_0 = points[0];
// //    auto &p_1 = points[1];
// //    auto &p_2 = points[2];
// //    auto &p_3 = points[3];
//    auto point;
//    for(double t = p_0.x; t <= p_1.x; t += 0.0001)
//    {
//     point.x = p_0.x;
//     point.y = t;
//      window.at<cv::Vec3b>(point.x, point.y)[2] = 255;
//    }
//     // for(double t = p_0.x; t <= p_1.x; t += 0.0001)
//     // {
//     //     double k = (p_0.y - p_1.y)/(p_0.x - p_1.x);
//     //     // auto point;
//     //     // point.x =  t;
//     //     // point.y = k * t;
//     //     double y = k*(t - p_1.x) + p_1.y;
//     //     window.at<cv::Vec3b>(t, y)[2] = 255;
//     // }
// }

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    ifstream readFile;
    readFile.open("/home/cs18/Desktop/graph.obj", ios::in);
    if(readFile.is_open())
    {
        cout << "open file success" << endl;
        char buff[1000] = {0};
        while(readFile >> buff)
        {
            cout << buff << endl;
        }
    }
    else
    {
        cout << "open fail" << endl;
    }
    readFile.close();
    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }
        if (control_points.size() == 4) 
        {
            // naive_bezier(control_points, window);
            bezier(control_points, window);
            // simple_Drow(control_points, window);
            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
