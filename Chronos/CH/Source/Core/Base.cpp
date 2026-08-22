#include <Core/Base.h>

using namespace chronos;

Base::Base(const BaseDesc& desc) : m_logger(desc.logger)
{
}

Base::~Base()
{
}

Logger& Base::getLogger() const noexcept
{
	return m_logger;
}