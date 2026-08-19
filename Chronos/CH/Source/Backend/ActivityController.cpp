#include <Backend/ActivityController.h>
#include <Analytics/ActivitySummary.h>
#include <Activity/Activity.h>
#include <Backend/RouteMacros.h>

chronos::ActivityController::ActivityController(const ActivityControllerDesc& desc) :
	Base(desc.base), m_summary(desc.summary), m_acManager(desc.acManager)
{
}

void chronos::ActivityController::registerRoutes(crow::App<CorsMiddleware>& app)
{
	CHRONOS_GET(app, "/api/activity/activetime", getRecentActiveTime);
}

crow::response chronos::ActivityController::getRecentActiveTime(const crow::request& req)
{
	UserId userId = 1;

	auto now = std::chrono::system_clock::now();
	auto today = std::chrono::floor<std::chrono::days>(now);
	Timestamp end = Activity::convertTimePoint(now);
	Timestamp begin = Activity::convertTimePoint(today);

	auto result = m_summary.calculateTotalDuration(begin, end);

	crow::json::wvalue response;
	response["duration"] = result.count();
	return crow::response(response);
}