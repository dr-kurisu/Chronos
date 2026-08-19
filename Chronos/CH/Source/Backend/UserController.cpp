#include <Backend/UserController.h>
#include <User/UserManager.h>
#include <Backend/RouteMacros.h>
#include <Application/Application.h>

chronos::UserController::UserController(const UserControllerDesc& desc) :
	Base(desc.base), m_userManager(desc.userManager), m_application(desc.application)
{

}

void chronos::UserController::registerRoutes(crow::App<CorsMiddleware>& app)
{
	CHRONOS_GET(app, "/api/user", getUser);
	CHRONOS_DELETE(app, "/api/user", removeUser);

	CHRONOS_POST(app, "/api/auth/register", registerUser);
	CHRONOS_POST(app, "/api/auth/login", login);
	CHRONOS_POST(app, "/api/auth/logout", logout);
}

crow::response chronos::UserController::registerUser(const crow::request& req)
{
	auto body = crow::json::load(req.body);
	if (!body) return crow::response(400, "Invalid JSON");

	if (!body.has("username") || !body.has("password"))
		return crow::response(400, "Missing username or password");

	const auto username = body["username"].s();
	const auto password = body["password"].s();
	if (!m_userManager.registerUser(username, password)) 
	{
		return crow::response(409, "Conflict User");
	}
	return crow::response(201);
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
	const auto user = m_userManager.getCurrentUser();
	if (!user) return crow::response(404);
	crow::json::wvalue response;
	response["id"] = user->id;
	response["name"] = user->name;
	response["createdTime"] = user->createdTime;
	return crow::response(200, response);
}

crow::response chronos::UserController::login(const crow::request& req)
{
	auto body = crow::json::load(req.body);
	if (!body) return crow::response(400, "Invalid JSON");
	if (!body.has("username") || !body.has("password"))
		return crow::response(400, "Missing username or password");
	const auto username = body["username"].s();
	const auto password = body["password"].s();

	if (!m_application.login(username, password)) 
	{
		return crow::response(401, "Invalid username or password");
	}
	return crow::response(200);
}

crow::response chronos::UserController::logout(const crow::request& req)
{
	m_application.logout();
	return crow::response(200);
}