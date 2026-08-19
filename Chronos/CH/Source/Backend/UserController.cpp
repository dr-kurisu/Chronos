#include <Backend/UserController.h>
#include <User/UserManager.h>

chronos::UserController::UserController(const UserControllerDesc& desc) :
	Base(desc.base), m_userManager(desc.userManager)
{

}

void chronos::UserController::registerRoutes(crow::App<CorsMiddleware>& app)
{

}
