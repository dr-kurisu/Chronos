#pragma once

#include <Windows.h>
#include <unknwn.h>
#include <WebView2.h>
#include <Core/Rect.h>
#include <wrl.h>

using Microsoft::WRL::Callback;
using Microsoft::WRL::ComPtr;

namespace chronos
{
    class WebViewController
    {
    public:        
        ~WebViewController();
        bool initialise(HWND hwnd);
        void resize(int, int);
    private:
        HWND m_hwnd{};
        Microsoft::WRL::ComPtr<ICoreWebView2Environment> m_environment{};
        ComPtr<ICoreWebView2Controller> m_controller;
        ComPtr<ICoreWebView2> m_webView;
    };
}
