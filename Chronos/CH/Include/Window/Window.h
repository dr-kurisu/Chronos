#pragma once

#include <Core/Base.h>
#include <Core/Rect.h>
#include <Windows.h>
#include <functional>

namespace chronos 
{
	class Window : public Base
	{
	public:
		explicit Window(const WindowDesc&);
		virtual ~Window() override;
		using ResizeCallback = std::function<void(int, int)>;
		void setResizeCallback(ResizeCallback);
		void onResize(int, int);

		HWND handle() const noexcept { return m_handle; }
	private:
		HWND m_handle{};
		Rect m_size;
		ResizeCallback m_resizeCallback;
	};
}