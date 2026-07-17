#pragma once
#include <Core/Core.h>
#include <Core/Logger.h>

namespace chronos {
	struct BaseDesc {
		Logger& logger;
	};

	struct ApplicationDesc {
		Logger::LogLevel level;
	};
};