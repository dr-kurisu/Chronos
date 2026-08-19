#pragma once

#include <Core/Core.h>
#include <Core/Base.h>
#include <Backend/CorsMiddleware.h>
#include <crow.h>

namespace chronos
{
	class UserController : public Base
	{
	public:
		UserController(const UserControllerDesc& desc);
		void registerRoutes(crow::App<CorsMiddleware>& app);

	private:
		UserManager& m_userManager;
	};
}