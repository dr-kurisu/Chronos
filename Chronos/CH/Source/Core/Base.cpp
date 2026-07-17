#include <Core/Base.h>

using namespace chronos;

Base::Base(const BaseDesc& desc) : m_logger(desc.logger)
{
}

Base::~Base()
{
}

Logger& Base::getLogger() noexcept
{
	return m_logger;
}