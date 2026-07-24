#include <Application/Application.h>
#include <Windows.h>
#include <iostream>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	try{
		chronos::Application application({ chronos::Logger::LogLevel::Info });
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