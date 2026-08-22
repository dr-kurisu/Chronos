#include <Backend/UserController.h>
#include <User/UserManager.h>
#include <Backend/RouteMacros.h>
#include <User/AuthContext.h>

chronos::UserController::UserController(const UserControllerDesc& desc) :
	Base(desc.base), m_userManager(desc.userManager), m_authContext(desc.authContext)
{
}

void chronos::UserController::registerRoutes(crow::App<CorsMiddleware>& app)
{
	CHRONOS_GET(app, "/api/user", getUser);
	CHRONOS_DELETE(app, "/api/user", removeUser);
}

crow::response chronos::UserController::removeUser(const crow::request& req)
{
	return crow::response(501, "Not implemented");
}

crow::response chronos::UserController::updateUser(const crow::request& req)
{
	return crow::response(501, "Not implemented");
}

crow::response chronos::UserController::getUser(const crow::request& req)
{
	const auto userId = m_authContext.userId();

	if (!userId) return crow::response(401, "Unauthorized");

	const auto user = m_userManager.findUser(*userId);
	if (!user) return crow::response(404, "User not found");
	crow::json::wvalue response;
	response["id"] = user->id;
	response["username"] = user->username;
	response["name"] = user->name;
	response["createdTime"] = user->createdTime;
	return crow::response(200, response);
}