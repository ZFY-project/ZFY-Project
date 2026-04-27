#pragma once
//颜色
struct Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
//二维空间位置
struct Vec2
{
	float x, y;
};
//三维空间
struct Vec3
{
	float x, y, z;
};
//三维旋转角
struct Angle
{
	float pitch;  // 绕X
	float yaw;    // 绕Y
	float roll;   // 绕Z
};

class Renderer
{
public:
	Renderer(int w, int h);
	~Renderer();

	//Rotate顶点旋转函数：传入3D点+旋转角度，返回旋转后的新3D坐标
	Vec3 rotate(Vec3 point, Angle angel);
	//Project透视投影函数：把旋转完的3D立体点，换算成屏幕2D平面坐标，自带近大远小
	Vec2 project(Vec3 point);
	//画布置黑
	void clear();
	// PutPixel画点函数：计算数组索引，指定位置上色
	void putPixel(int x, int y, Color color);
	//DrawLine画线函数：底层算法两点之间连续描点连线
	void drawLine(int x1, int y1, int x2, int y2, Color color);

	unsigned char* m_buffer;//后台离屏像素缓冲区 一维数组

private:
	int m_width;//画布宽度
	int m_height;//画布高度

};

