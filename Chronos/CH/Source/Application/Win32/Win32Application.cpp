#include <Application/Application.h>
#include <Windows.h>

void chronos::Application::run() {
    MSG msg;

    while (m_isRunning)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }
}