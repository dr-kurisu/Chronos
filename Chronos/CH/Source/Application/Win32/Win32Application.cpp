#include <Core/All.h>

void chronos::Application::run() {
    // Login default account
    login();
    // Get current AC
    m_acManager->createCurrentActivity(m_monitor->getCurrentForeground());
    ChronosLogInfo("Chronos Lanuched");
    ChronosLogInfo("------------------------------------------");

    // Backend Run
    std::thread backendThread([this]()
    {
        m_backend->run();
    });

    MSG msg;
    while (m_isRunning)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
        {
            if (msg.message == WM_QUIT) {
                m_isRunning = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    m_backend->stop();
    // Wait for backend thread
    if (backendThread.joinable())
    {
        backendThread.join();
    }
}
