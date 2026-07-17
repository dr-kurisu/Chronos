#include <Application/Application.h>

int main() {
	try{
		chronos::Application application({ chronos::Logger::LogLevel::Info });
		application.run();
		return 0;
	}
	catch (const std::runtime_error&) {
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument&) {
		return EXIT_FAILURE;
	}
	catch (...) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}