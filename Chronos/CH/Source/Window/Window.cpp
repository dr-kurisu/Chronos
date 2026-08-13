#include <Window/Window.h>
#include <Windows.h>
#include <stdexcept>

using namespace chronos;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	// creation
	case WM_NCCREATE:
	{
		auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		auto window = static_cast<Window*>(cs->lpCreateParams);

		SetWindowLongPtr(
			hwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(window));

		return TRUE;
	}
	// destroy
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	// resize
	case WM_SIZE:
	{
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (window) {
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			window->onResize(height, width);
		}
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return FALSE;
}


Window::Window(const WindowDesc& desc) : Base(desc.base), m_size(desc.size) {
	auto registerWindowClassFunction = []()
		{
			WNDCLASSEX wc{};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = L"ChronosWindowClass";
			wc.lpfnWndProc = WindowProc;
			return RegisterClassEx(&wc);
		};

	static const auto windowClassId = registerWindowClassFunction();


	// fail to create window
	if (!windowClassId) {
		ChronosLogThrowError("RegisterClassEx Failed.");
	}

	RECT rc = { 0, 0, m_size.width, m_size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

	m_handle = CreateWindowEx(
		NULL, 
		MAKEINTATOM(windowClassId), 
		L"Chronos | WebView2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left, 
		rc.bottom - rc.top,
		NULL, 
		NULL, 
		NULL, 
		this
	);
	if (!m_handle) {
		ChronosLogThrowError("CreateWindowEx failed");
	}
	ShowWindow(m_handle, SW_SHOW);
}


Window::~Window() {
	DestroyWindow(static_cast<HWND>(m_handle));
}

void chronos::Window::setResizeCallback(ResizeCallback callback)
{
	m_resizeCallback = callback;
}

void chronos::Window::onResize(int width, int height)
{
	if (m_resizeCallback)
	{
		m_resizeCallback(width, height);
	}
}
