#include "Renderer.h"
#define _USE_MATH_DEFINES 
#include <cmath>

Renderer::Renderer(int w, int h)
	:m_width(w), m_height(h)
{
	int totalSize = m_width * m_height * 3;//总字节数内存（你要画一幅画：算你需要多大的纸）
	m_buffer = new unsigned char[totalSize];//为画布动态申请内存（去商店买一张这么大的白纸）
}

Renderer::~Renderer()
{
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
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;

	while (true) {
		putPixel(x1, y1, color);
		if (x1 == x2 && y1 == y2) break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x1 += sx; }
		if (e2 < dx) { err += dx; y1 += sy; }
	}
}

Vec3 Renderer::rotate(Vec3 point, Angle angle)
{
	//转弧度
	float radX = angle.pitch * M_PI / 180.0f;
	float radY = angle.yaw * M_PI / 180.0f;
	float radZ = angle.roll * M_PI / 180.0f;

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

Vec2 Renderer::project(Vec3 point)
{
	//固定参数
	float focalLength = 800.0f;//焦距
	float nearClip = 0.1f;
	//深度判断
	if (point.z < nearClip)
	{
		return{ 0,0 };
	}
	float scale = focalLength / point.z;//放大倍数
	auto x = point.x * scale;
	auto y = point.y * scale;

	//翻转y轴(3D 数学世界：Y 轴向上是正,电脑屏幕：Y轴向下是正,如果不翻转你画出来的3D物体会 上下颠倒、头朝下。)
	y = -y;

	//把点从屏幕中心 → 移到正确的像素位置
	x += m_width / 2.0f;
	y += m_height / 2.0f;
	return { x,y };
}
