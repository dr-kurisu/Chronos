#pragma once

#include <Core/Core.h>
#include <Core/Base.h>
#include <Backend/CorsMiddleware.h>
#include <crow.h>

namespace chronos 
{
	class ActivityController : public Base
	{
	public:
		ActivityController(const ActivityControllerDesc& desc);
		void registerRoutes(crow::App<CorsMiddleware>& app);

	private:
		crow::response getRecentActiveTime(const crow::request& req);

	private:
		ActivitySummary& m_summary;
		ActivityManager& m_acManager;
	};
}