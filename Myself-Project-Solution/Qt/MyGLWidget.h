#pragma once
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QOpenGLShaderProgram>
#include<QOpenGLFunctions_3_3_Core>
#include <vector>
class MyGLWidget :
    public QOpenGLWidget
    , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    MyGLWidget(QWidget* parent = nullptr);
    ~MyGLWidget();
protected:
    // OpenGL生命周期函数
    void initializeGL()override;//初始化
    void paintGL()override;//渲染
    void resizeGL(int w, int h);
    //鼠标键盘交互
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;
private:
    // ===== OpenGL对象 =====
    GLuint VAO;
    /*
    全称：Vertex Array Object 顶点数组对象用来记录显卡怎么读取顶点数据你画三角形、
    立方体都要靠它,只用在：initializeGL、paintGL
    */
    GLuint VBO;
    /*
    全称：Vertex Buffer Object 顶点缓冲对象用来把顶点数据从 CPU 传到显卡
    存的是坐标点和 VAO 配对使用
    */
    QOpenGLShaderProgram shader;
    /*
    管理顶点着色器 + 片段着色器作用：告诉显卡怎么画、画什么颜色
    */

    // ===== 几何数据 =====
    std::vector<float> vertices;//顶点数据数组（要画的形状）

    // ===== 相机参数 =====
    float yaw;    // 左右旋转
    float pitch;  // 上下旋转
    float distance;
    /*
    相机离物体的距离
    数值越大 → 离得越远 → 物体越小
        作用：缩放视角
    */

    QPoint lastMousePos;

    // ===== 工具函数 =====
    void updateVBO(); // 更新GPU数据

};

