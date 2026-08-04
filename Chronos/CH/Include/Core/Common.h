#pragma once
#include <Core/Core.h>
#include <Core/Logger.h>
#include <filesystem>
#include <chrono>

namespace chronos {
	struct BaseDesc {
		Logger& logger;
	};

	struct ApplicationDesc {
		Logger::LogLevel level;
		std::filesystem::path storagePath = "";
	};

	struct WindowsWatcherDesc {
		BaseDesc base;
		float duration;
	};

	struct MonitorDesc {
		BaseDesc base;
	};

	struct ActivityClassifierDesc {
		BaseDesc base;
		IActivityStorage& storage;
	};

	struct ActivityManagerDesc {
		BaseDesc base;
		bool enableStorage = true;
		bool captureWindowTitle = true;
		bool captureProcessPath = true;
		std::chrono::seconds minDuration{ 10 };
		size_t maxEventCacheSize = 128;
		IActivityStorage& storage;
	};

	struct SQLiteStorageDesc {
		BaseDesc base;
		SQLiteDatabase& db;
	};

	struct SQLiteDatabaseDesc {
		BaseDesc base;
		std::filesystem::path storagePath = "";
	};

	struct UserManagerDesc {
		BaseDesc base;
		IUserStorage& storage;
	};

	struct ActivitySummaryDesc {
		BaseDesc base;
		ISummaryGenerator& generator;
	};

	struct PlanManagerDesc {
		BaseDesc base;
		IActivityStorage& storage;
	};
};