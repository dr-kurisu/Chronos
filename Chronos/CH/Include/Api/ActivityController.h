#pragma once

#include <Core/Core.h>
#include <Core/Base.h>

namespace chronos 
{
	class ActivityController : public Base 
	{
	public:
		ActivityController(const ActivityControllerDesc& desc);
		//Json::Value getTotalActiveTime(Timestamp begin, Timestamp end);

	private:
		ActivitySummary& m_summary;
	};
}