#include <Backend/Backend.h>
#include <Backend/ActivityController.h>
#include <Backend/UserController.h>

chronos::Backend::Backend(const BackendDesc& desc): 
    Base(desc.base), m_acController(desc.acController), m_userController(desc.userController), m_port(desc.port)
{
    registerRoutes();
}

chronos::Backend::~Backend()
{
    stop();
}

void chronos::Backend::run()
{
    m_app.loglevel(crow::LogLevel::Warning);
    m_app.port(m_port).multithreaded().run();
}

void chronos::Backend::stop()
{
    m_app.stop();
}

void chronos::Backend::registerRoutes()
{
    m_acController.registerRoutes(m_app);
    m_userController.registerRoutes(m_app);
}
