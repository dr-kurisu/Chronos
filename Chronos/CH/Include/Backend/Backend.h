#pragma once

#include <Core/Core.h>
#include <Core/Base.h>
#include <Backend/CorsMiddleware.h>
#include <crow.h>


namespace chronos
{
    class Backend : public Base
    {
        disable_copy_and_move(Backend);
    public:
        explicit Backend(const BackendDesc& desc);
        ~Backend();

        void run();
        void stop();

    private:
        void registerRoutes();

    private:
        uint16_t m_port;
        crow::App<CorsMiddleware> m_app;
        ActivityController& m_acController;
        UserController& m_userController;
    };
}