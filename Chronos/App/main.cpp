#include <Application/Application.h>
#include <Windows.h>
#include <iostream>
#include <Core/Common.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	SetProcessDPIAware();

	try{
		chronos::Application application(chronos::ApplicationDesc{
			.level = chronos::Logger::LogLevel::Info,
			.storagePath = "C:/Users/24156/source/repos/Chronos/Chronos/CH/Data/chronos.db",
			.display = false
		});
		application.run();
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr
			<< "[Fatal] "
			<< e.what()
			<< std::endl;

		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "UNKNOWN ERROR" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}