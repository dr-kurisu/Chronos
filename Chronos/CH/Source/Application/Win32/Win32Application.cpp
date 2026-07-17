#include <Application/Application.h>
#include <thread>

void chronos::Application::run() {
	while (m_isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}