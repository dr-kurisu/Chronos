#pragma once
#include <Core/Core.h>
#include <Core/Logger.h>
#include <Core/Rect.h>

#include <filesystem>
#include <chrono>


namespace chronos {
	struct BaseDesc
	{
		Logger& logger;
	};

	struct ApplicationDesc
	{
		Logger::LogLevel level;
		std::filesystem::path storagePath = "";
		bool display = false;
	};

	struct WindowsWatcherDesc
	{
		BaseDesc base;
		float duration;
	};

	struct MonitorDesc
	{
		BaseDesc base;
	};

	struct ActivityClassifierDesc
	{
		BaseDesc base;
	};

	struct ActivityManagerDesc
	{
		BaseDesc base;
		bool enableStorage = true;
		bool captureWindowTitle = true;
		bool captureProcessPath = true;
		std::chrono::seconds minDuration{ 10 };
		size_t maxEventCacheSize = 128;
		IActivityStorage& storage;
	};

	struct SQLiteStorageDesc
	{
		BaseDesc base;
		SQLiteDatabase& db;
	};

	struct SQLiteDatabaseDesc
	{
		BaseDesc base;
		std::filesystem::path storagePath = "";
	};

	struct UserManagerDesc
	{
		BaseDesc base;
		IUserStorage& storage;
	};

	struct TagManagerDesc
	{
		BaseDesc base;
		ITagStorage& storage;
	};

	struct ActivitySummaryDesc
	{
		BaseDesc base;
		IActivityStorage& acStorage;
		ITagStorage& tagStorage;
		ISummaryGenerator& generator;
	};

	struct PlanManagerDesc
	{
		BaseDesc base;
		IPlanStorage& storage;
	};

	struct WindowDesc
	{
		BaseDesc base;
		Rect size;
	};

	struct BackendDesc
	{
		BaseDesc base;
		ActivityController& acController;
		UserController& userController;
		uint16_t port;
	};

	struct ActivityControllerDesc
	{
		BaseDesc base;
		ActivitySummary& summary;
		ActivityManager& acManager;
	};

	struct UserControllerDesc 
	{
		BaseDesc base;
		UserManager& userManager;
	};
};