#pragma once

#define CHRONOS_GET(app, path, handler) \
    CROW_ROUTE(app, path) \
        .methods(crow::HTTPMethod::GET) \
        ([this](const crow::request& req) { \
            return handler(req); \
        })

#define CHRONOS_POST(app, path, handler) \
    CROW_ROUTE(app, path) \
        .methods(crow::HTTPMethod::POST) \
        ([this](const crow::request& req) { \
            return handler(req); \
        })

#define CHRONOS_DELETE(app, path, handler) \
    CROW_ROUTE(app, path) \
        .methods(crow::HTTPMethod::Delete) \
        ([this](const crow::request& req) { \
            return handler(req); \
        })
