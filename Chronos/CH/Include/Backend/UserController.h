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
		crow::response getUser(const crow::request& req);
		crow::response updateUser(const crow::request& req);
		crow::response removeUser(const crow::request& req);

	private:
		UserManager& m_userManager;
		AuthContext& m_authContext;
	};
}