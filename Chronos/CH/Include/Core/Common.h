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
	};

	struct ActivityManagerDesc {
		BaseDesc base;
		bool enableStorage = true;
		bool captureWindowTitle = true;
		bool captureProcessPath = true;
		std::chrono::seconds minDuration{ 10 };
		size_t maxEventCacheSize = 128;
		std::filesystem::path storagePath = "";
	};

	struct SQLiteACStorageDesc {
		BaseDesc base;
		std::filesystem::path storagePath = "";
	};
};