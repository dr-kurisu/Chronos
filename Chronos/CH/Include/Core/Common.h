#pragma once
#include <Core/Core.h>
#include <Core/Logger.h>
#include <filesystem>

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

	struct ActivityManagerDesc {
		BaseDesc base;
		bool enableStorage = true;
		bool captureWindowTitle = true;
		bool captureProcessPath = true;
		size_t maxEventCacheSize = 128;
		std::filesystem::path storagePath = "data/activity";
	};
};