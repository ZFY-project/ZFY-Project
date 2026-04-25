#include "Renderer.h"
#define _USE_MATH_DEFINES 
#include <cmath>

Renderer::Renderer(int w, int h)
	:m_width(w),m_height(h)
{
	int totalSize = m_width * m_height * 3;//总字节数内存（你要画一幅画：算你需要多大的纸）
	m_buffer = new unsigned char[totalSize];//为画布动态申请内存（去商店买一张这么大的白纸）
}

void Renderer::clear()
{
	for (int i = 0;i < m_width * m_height * 3;i++)
	{
		m_buffer[i] = 0;
	}
}

void Renderer::putPixel(int x, int y, Color color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;

	int index = (y * m_width + x) * 3;
	// 给 R G B 三个通道上色
	m_buffer[index + 0] = color.R;
	m_buffer[index + 1] = color.G;
	m_buffer[index + 2] = color.B;
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, Color color)
{
	auto dx = x2 - x1;
	auto dy = y2 - y1;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float xInc = dx / (float)steps;
	float yInc = dy / (float)steps;

	// 从起点开始走
	float x = x1;
	float y = y1;

	// 一步一步画点
	for (int i = 0; i <= steps; i++)
	{
		putPixel((int)x, (int)y, color);
		x += xInc;
		y += yInc;
	}
}

Vec3 Renderer::rotate(Vec3 point, Angle angle)
{
	//转弧度
	float radX = angle.pitch * M_PI / 180.0f;
	float radY = angle.roll * M_PI / 180.0f;
	float radZ = angle.yaw * M_PI / 180.0f;

	float sx = sin(radX), cx = cos(radX);
	float sy = sin(radY), cy = cos(radY);
	float sz = sin(radZ), cz = cos(radZ);

	auto x = point.x;
	auto y = point.y;
	auto z = point.z;
	// 绕X
	float y1 = y * cx - z * sx;
	float z1 = y * sx + z * cx;
	y = y1;
	z = z1;
	// 绕Y
	float x2 = x * cy + z * sy;
	float z2 = -x * sy + z * cy;
	x = x2;
	z = z2;
	// 绕Z
	float x3 = x * cz - y * sz;
	float y3 = x * sz + y * cz;
	x = x3;
	y = y3;
	return { x,y,z };
}

Vec2 Renderer::project(const Vec3 &point)
{

	return Vec2();
}
