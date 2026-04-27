#include "MyApp.h"

MyApp::MyApp(int width, int height)
    : m_width(width), m_height(height),
    m_isDrag(false), m_lastX(0), m_lastY(0),
    m_yaw(0), m_pitch(0)
{
    m_renderer = new Renderer(width, height);
    InitWindow();
}

MyApp::~MyApp()
{
    delete m_renderer;
}

void MyApp::InitWindow()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"3DWin";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassEx(&wc);

    m_hwnd = CreateWindowEx(
        0, L"3DWin", L"3DäÖÈ¾", WS_OVERLAPPEDWINDOW,
        100, 100, m_width, m_height,
        NULL, NULL, hInstance, NULL
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
}

void MyApp::Run()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK MyApp::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MyApp* app = (MyApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (!app) return DefWindowProc(hwnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_LBUTTONDOWN:
        app->m_isDrag = true;
        app->m_lastX = LOWORD(lParam);
        app->m_lastY = HIWORD(lParam);
        break;

    case WM_MOUSEMOVE:
        if (app->m_isDrag)
        {
            int curX = LOWORD(lParam);
            int curY = HIWORD(lParam);
            int dx = curX - app->m_lastX;
            int dy = curY - app->m_lastY;

            app->m_yaw += dx * 0.5f;
            app->m_pitch += dy * 0.5f;

            app->m_lastX = curX;
            app->m_lastY = curY;
            InvalidateRect(hwnd, nullptr, true);
        }
        break;

    case WM_LBUTTONUP:
        app->m_isDrag = false;
        break;

    case WM_PAINT:
    {
        Renderer* r = app->m_renderer;
        r->clear();

        int radius = 50;
        Angle ang = { app->m_pitch, app->m_yaw, 0.0f };
        Vec3 point[8] = {
            {-radius, -radius, -radius + 250},
            {radius, -radius, -radius + 250},
            {radius, radius, -radius + 250},
            {-radius, radius, -radius + 250},
            {-radius, -radius, radius + 250},
            {radius, -radius, radius + 250},
            {radius, radius, radius + 250},
            {-radius, radius, radius + 250},
        };

        int edges[] = {
            0,1,1,2,2,3,3,0,
            4,5,5,6,6,7,7,4,
            0,4,1,5,2,6,3,7
        };

        for (int i = 0; i < 12; i++)
        {
            int id1 = edges[i * 2];
            int id2 = edges[i * 2 + 1];
            Vec3 p1 = point[id1];
            Vec3 p2 = point[id2];
            Vec3 r1 = r->rotate(p1, ang);
            Vec3 r2 = r->rotate(p2, ang);
            Vec2 s1 = r->project(r1);
            Vec2 s2 = r->project(r2);
            Color white = { 255,255,255 };
            r->drawLine((int)s1.x, (int)s1.y, (int)s2.x, (int)s2.y, white);
        }

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(hdc, &ps.rcPaint, blackBrush);
        DeleteObject(blackBrush);

        BITMAPINFOHEADER bih = {};
        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biWidth = 800;
        bih.biHeight = -600;
        bih.biPlanes = 1;
        bih.biBitCount = 24;
        bih.biCompression = BI_RGB;

        SetDIBitsToDevice(
            hdc, 0, 0, 800, 600,
            0, 0, 0, 600,
            r->m_buffer,
            (BITMAPINFO*)&bih,
            DIB_RGB_COLORS
        );

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}