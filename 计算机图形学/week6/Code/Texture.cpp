//
// Created by LEI XU on 4/27/19.
//
 
#include "Texture.hpp"
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
 

 
// my func
float adjust_by_range(float x, float x_min, float x_max)
{
    if (x < x_min) return x_min;
    if (x > x_max) return x_max;
    return x;
}
 
Eigen::Vector3f Texture::getColor(float u, float v)
{
    // 防止数组越界
    u = adjust_by_range(u, 0, 1.0f);
    v = adjust_by_range(v, 0, 1.0f);
 
    auto u_img = u * (width - 1);
    auto v_img = (1 - v) * (height-1);
    auto color = image_data.at<cv::Vec3b>(v_img, u_img);
    return Eigen::Vector3f(color[0], color[1], color[2]);
}
 // my func
cv::Vec3b lerp(float x, cv::Vec3b v0, cv::Vec3b v1)
{
    return v0 + x*(v1-v0);
};
Eigen::Vector3f Texture::getColorBilinear(float u,float v)
{
    // 防止数组越界
    u = adjust_by_range(u, 0, 1.0f);
    v = adjust_by_range(v, 0, 1.0f);
 
    // height和width都-1是指数组从0开始    
    float u_img = u * (width - 1);
    float v_img = (1 - v) * (height - 1);
 
    float u_min = std::floor(u_img);
    float u_max = std::ceil(u_img);
    float v_min = std::floor(v_img);
    float v_max = std::ceil(v_img);
 
    // auto color = image_data.at<cv::Vec3b>(v_img, u_img);
    auto u00 = image_data.at<cv::Vec3b>(v_min, u_min);
    auto u10 = image_data.at<cv::Vec3b>(v_min, u_max);
    auto u01 = image_data.at<cv::Vec3b>(v_max, u_min);
    auto u11 = image_data.at<cv::Vec3b>(v_max, u_max);
 
    float s = (u_img - u_min) / (u_max - u_min);
    float t = (v_img - v_min) / (v_max - v_min);
 
    auto u0 = lerp(s, u00, u10);
    auto u1 = lerp(s, u01, u11);
 
    auto result = lerp(t, u0, u1);
    
    return Eigen::Vector3f(result[0], result[1], result[2]);
};