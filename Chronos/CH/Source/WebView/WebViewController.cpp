#include <WebView/WebViewController.h>
#include <iostream>

chronos::WebViewController::~WebViewController()
{
}

bool chronos::WebViewController::initialise(HWND hwnd)
{
	m_hwnd = hwnd;
    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
        nullptr,
        nullptr,
        nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment* environment)
            -> HRESULT
            {
                if (FAILED(result))
                {
                    return result;
                }
                m_environment = environment;
                m_environment->CreateCoreWebView2Controller(
                    m_hwnd,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this](HRESULT result, ICoreWebView2Controller* controller)
                        -> HRESULT
                        {
                            if (FAILED(result))
                            {
                                return result;
                            }

                            m_controller = controller;

                            m_controller->get_CoreWebView2(
                                &m_webView
                            );

                            RECT bounds{};
                            GetClientRect(
                                m_hwnd,
                                &bounds
                            );

                            m_controller->put_Bounds(
                                bounds
                            );

                            // loading website
                            m_webView->Navigate(
                                L"http://localhost:5173"
                            );

                            return S_OK;
                        }
                    ).Get()
                );

                return S_OK;
            }
        ).Get()
    );

    return SUCCEEDED(hr);
}

void chronos::WebViewController::resize(int width, int height)
{
    if (!m_controller)
        return;

    RECT bounds{ 0, 0, width, height };
    GetClientRect(m_hwnd, &bounds);
    m_controller->put_Bounds(bounds);
}