#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;
    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    rotation_angle = rotation_angle / 180 * M_PI;
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f translate;
    translate << cos(rotation_angle), -sin(rotation_angle), 0, 0,
        sin(rotation_angle), cos(rotation_angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    model = translate * model;
    return model;
}

Eigen::Matrix4f get_model_matrix_axis(float rotation_angle, Eigen::Vector3f axis_start, Eigen::Vector3f axis_end)
{
	// Eigen::Vector3f axis_start 为起点
	// Eigen::Vector3f axis_end 为终点
	Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
	// normalize axis
	Eigen::Vector3f axis;
	axis[0] = axis_end[0] - axis_start[0];
	axis[1] = axis_end[1] - axis_start[1];
	axis[2] = axis_end[2] - axis_start[2];
	float norm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	axis[0] /= norm;
	axis[1] /= norm;
	axis[2] /= norm;
	// compute radian
	float radian = rotation_angle / 180.0 * MY_PI;
	// compute component 计算轴角旋转矩阵分量
	Eigen::Matrix3f n(3, 3);
	n << 0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0;

	Eigen::Matrix3f component1 = Eigen::Matrix3f::Identity() * cos(radian);
	Eigen::Matrix3f component2 = axis * axis.transpose() * (1 - cos(radian));
	Eigen::Matrix3f component3 = n * sin(radian);	

	Eigen::Matrix3f rotate_m = component1 + component2 + component3;
	
	// Eigen 自带构造轴角旋转矩阵
	// 下列注释用于验证我们构造的轴角旋转矩阵是否和Eigen的构造的轴角旋转矩阵一致
	//Eigen::AngleAxisf rotation_vector(radian, Vector3f(axis[0], axis[1], axis[2]));  
	//Eigen::Matrix3f rotation_matrix;
	//rotation_m = rotation_vector.toRotationMatrix();

	Eigen::Matrix4f rotate_martix = Eigen::Matrix4f::Identity();
	rotate_martix.block(0, 0, 3, 3) = rotate_m; // 前三个维度为旋转矩阵

	model = rotate_martix * model;
	return model;
}


Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{
	Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

	//透视图，近大远小，是个视锥  此矩阵是一个公式
	Eigen::Matrix4f pto = Eigen::Matrix4f::Identity();//将透视矩阵挤压成正交矩阵
	pto << zNear, 0, 0, 0,
		0, zNear, 0, 0,
		0, 0, zNear + zFar, - zFar * zNear,
		0, 0, 1.0, 0;

	float halfAngle = (eye_fov / 2.0 / 180.0) * MY_PI; //视角的一半
	float top = -1.0f * zNear * tan(halfAngle);//y轴正方向值 = 显示视口的一半高度
	float right= top * aspect_ratio;
	float bottom = -top;
	float left = -right;

	//构造缩放矩阵，使视口大小等同窗口大小
	Eigen::Matrix4f m_s = Eigen::Matrix4f::Identity();
	m_s << 2 / (right - left), 0, 0, 0,			
			0, 2 / (top - bottom), 0, 0,				//缩放的倍数为 期望值/当前值
			0, 0, 2 / (zNear - zFar), 0,				//所以缩放的倍数为 (1+1)/某一维度的当前值
			0, 0, 0, 1;

	//构造平移矩阵，将视口左下角移动到原点
	Eigen::Matrix4f m_t = Eigen::Matrix4f::Identity();
	
	//左侧+右侧或者上侧+下侧，结果都是0,但这里为了便于理解或者防止参数变动之后会产生的一系列变化还是选用公式的写法
	m_t << 1, 0, 0, -(left+right)/2.0f,					
			0, 1, 0, -(top+bottom)/2.0f,					
			0, 0, 1, -(zNear+zFar)/2.0f,
			0, 0, 0, 1;
	
	projection = m_s * m_t * pto * projection;
	
	return projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false; // judge if show in screen
    std::string filename = "output.png";

    if (argc >= 3)  // don`t need show in screen, it will store in picture
    {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4)    // argv[3] is the filename
        {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);
        return 0;
    }


    Eigen::Vector3f start = {0, 0, 0};
    Eigen::Vector3f end = {0, 2, 0};
    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix_axis(angle, start, end));
        // r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
