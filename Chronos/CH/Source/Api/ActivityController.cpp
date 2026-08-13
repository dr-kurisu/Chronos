#include <Api/ActivityController.h>

chronos::ActivityController::ActivityController(const ActivityControllerDesc& desc) :
	Base(desc.base), m_summary(desc.summary)
{

}

//Json::Value chronos::ActivityController::getTotalActiveTime(Timestamp begin, Timestamp end)
//{
//	return Json::Value();
//}


