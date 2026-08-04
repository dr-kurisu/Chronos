#pragma once

#include <Core/Base.h>

namespace chronos {
	class ActivityClassifier : public Base {
	public:
		ActivityClassifier(const ActivityClassifierDesc& desc);
		void classify(Activity& ac);
	private:
		void classifyByWindows(Activity& ac);
		void classifyByProcess(Activity& ac);

	private:
		IActivityStorage& m_storage;
	};
}