#pragma once

#include <glad/glad.h>    // 加载 OpenGL 函数指针（必须最先包含）
#include <GLFW/glfw3.h>   // 创建窗口、处理输入
#include <glm/glm.hpp>    // 数学库（向量、矩阵）
#include <glm/gtc/matrix_transform.hpp>  // 矩阵变换（旋转、平移等）
#include <glm/gtc/type_ptr.hpp>          // 矩阵转指针，传给着色器

class MyOpenGL
{
public:
    MyOpenGL(int width, int height);  // 构造函数：初始化窗口大小
    ~MyOpenGL();                      // 析构函数：释放资源

    void Run();  // 主循环：启动程序

private:
    void Init();         // 初始化：GLFW、GLAD、着色器、三角形
    void CreateShader(); // 创建并编译着色器
    void CreateTriangle();// 创建三角形顶点数据
    void Render();       // 每一帧绘制画面

private:
    GLFWwindow* window;  // 窗口指针
    int w, h;            // 窗口宽高

    unsigned int shader; // 着色器程序ID
    unsigned int VAO, VBO; // 顶点数组对象、顶点缓冲对象
};