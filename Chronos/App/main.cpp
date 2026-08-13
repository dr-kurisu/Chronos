#include <Application/Application.h>
#include <Windows.h>
#include <iostream>
#include <crow.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	SetProcessDPIAware();

	crow::SimpleApp app;

	CROW_ROUTE(app, "/")
		([] {
		return "Chronos Backend";
			});
	app.port(18080).multithreaded().run();

	try{
		chronos::Application application({ chronos::Logger::LogLevel::Info, "C:/Users/24156/source/repos/Chronos/Chronos/CH/Data/chronos.db"});
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