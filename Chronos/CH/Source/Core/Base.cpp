#include <Core/Base.h>

using namespace Chronos;

Base::Base(const BaseDesc& desc) : m_logger(desc.logger)
{
}

Base::~Base()
{
}

Logger& Base::getLogger() 
{
	return m_logger;
}