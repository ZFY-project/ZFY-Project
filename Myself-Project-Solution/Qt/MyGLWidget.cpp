#include "MyGLWidget.h"
#include <QMatrix4x4>

MyGLWidget::MyGLWidget(QWidget* parent)
    :QOpenGLWidget(parent)
{
    //初始化相机
    yaw = 0.0f;
    pitch = 0.0f;
    distance = 2.0f;

    // 初始化矩形（两个三角形）
    vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,

        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();// ✅ 必须：初始化OpenGL函数
    glEnable(GL_DEPTH_TEST);//开启深度测试（3D必须）

    // ===== 创建VAO/VBO（必须）=====
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // ===== 绑定（必须）=====
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // ===== CPU数据 → GPU（必须）=====(把 CPU 里的顶点数据 → 复制发送到显卡的 VBO 里)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
    /*
    * 参数
    1.我要往刚才绑定的 VBO 里传数据
    2.显卡必须知道：你要传多少数据
    3.CPU 里顶点数据的内存地址
    4.数据使用频率
    */

    // ===== 告诉GPU数据结构（必须）=====
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    /*
    1.顶点属性位置（location = 0）对应你顶点着色器里的：layout (location = 0) in vec3 aPos;
    2.顶点3D x y z 三个  2D x y两个
    3.数据类型是 float
    4.是否需要把数据归一化 0~1，顶点坐标一律填 false！
    */
    glEnableVertexAttribArray(0);// 开启 0号通道，允许数据传输

    // ===== Shader（必须）=====
    //顶点着色器- 决定物体画在哪里（位置 / 旋转 / 3D）
    shader.addShaderFromSourceCode(QOpenGLShader::Vertex,
        R"(#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
})");
    //片段着色器-决定物体是什么颜色
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment,
        R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.2, 0.7, 0.3, 1.0);
})");

    shader.link();
}

void MyGLWidget::paintGL()
{
    // ⭐ 必须：清屏（清空颜色|清空深度
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();//启用着色器

    QMatrix4x4 model;//模型矩阵（物体自身旋转、位移）
    QMatrix4x4 view;//相机矩阵（你眼睛看出去的视角）
    QMatrix4x4 proj;//投影矩阵（产生近大远小透视效果）

    // 相机后退
    view.translate(0, 0, -distance);
    // 鼠标控制旋转
    view.rotate(pitch, 1, 0, 0);//绕x轴
    view.rotate(yaw, 0, 1, 0);//绕y轴
    // 投影
    proj.perspective(45.0f, float(width()) / height(), 0.1f, 100.0f);

    //最终矩阵-MVP = 投影 × 相机 × 模型(顺序不能反）
    QMatrix4x4 mvp = proj * view * model;
    //把 CPU 算好的 MVP 矩阵 → 发给显卡着色器！对应着色器里的：uniform mat4 MVP;
    shader.setUniformValue("MVP", mvp);
    glBindVertexArray(VAO);
    // ⭐ 必须：发起绘制
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MyGLWidget::resizeGL(int w, int h)
{
}

void MyGLWidget::mousePressEvent(QMouseEvent* event)
{
    //记录鼠标【按下瞬间】的坐标
    lastMousePos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->pos().x() - lastMousePos.x();
    float dy = event->pos().y() - lastMousePos.y();
    yaw += dx * 0.5f;   // 左右旋转(0.5是灵敏度越大转的越快)
    pitch += dy * 0.5f; // 上下旋转
    lastMousePos = event->pos();
    update();//触发paintGL
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Right)
    {
        // ⭐ 修改右侧顶点（x变大）
        vertices[3] += 0.1f;
        vertices[6] += 0.1f;
        vertices[9] += 0.1f;
        vertices[12] += 0.1f;

        updateVBO(); // ⭐ 更新GPU
        update();    // ⭐ 重新绘制
    }
}

void MyGLWidget::updateVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // ⭐ CPU → GPU（更新）
    glBufferSubData(GL_ARRAY_BUFFER,
        0,
        vertices.size() * sizeof(float),
        vertices.data());
}
