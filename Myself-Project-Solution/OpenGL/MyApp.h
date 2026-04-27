#pragma once
#include <Windows.h>
#include "Renderer.h"

class MyApp
{
public:
    MyApp(int width, int height);
    ~MyApp();

    void Run();

private:
    void InitWindow();
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    int m_width;
    int m_height;
    HWND m_hwnd;
    Renderer* m_renderer;

    // Êó±ê¿ØÖÆ
    bool m_isDrag;
    int m_lastX;
    int m_lastY;
    float m_yaw;
    float m_pitch;
};

