#pragma once

#include <crow.h>

namespace chronos
{

    struct CorsMiddleware
    {
        struct context
        {
        };

        void before_handle(
            crow::request& req,
            crow::response& res,
            context&)
        {
        }

        void after_handle(
            crow::request&,
            crow::response& response,
            context&)
        {
            response.set_header(
                "Access-Control-Allow-Origin",
                "http://localhost:5173"
            );

            response.set_header(
                "Access-Control-Allow-Methods",
                "GET, POST, PUT, DELETE, OPTIONS"
            );

            response.set_header(
                "Access-Control-Allow-Headers",
                "Content-Type, Authorization"
            );

            response.set_header(
                "Access-Control-Allow-Credentials",
                "true"
            );
        }
    };

}