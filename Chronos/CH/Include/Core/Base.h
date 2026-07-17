#pragma once
#include <Core/Common.h>

namespace Chronos {
	class Base {
		disable_copy_and_move(Base);
	public:
		explicit Base(const BaseDesc& desc);
		virtual ~Base();
		virtual Logger& getLogger() noexcept final;
	protected:
		Logger& m_logger;
	};
}