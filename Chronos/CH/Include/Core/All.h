#pragma once

#include <Application/Application.h>
#include <Core/Logger.h>

#include <Activity/ActivityManager.h>
#include <User/UserManager.h>
#include <Tag/TagManager.h>
#include <User/SessionManager.h>


#include <Storage/SQliteDatabase.h>
#include <Storage/SQLiteActivityStorage.h>
#include <Storage/SQLiteTagStorage.h>
#include <Activity/Activity.h>


#include <Storage/SQLiteUserStorage.h>
#include <Storage/SQLitePlanStorage.h>
#include <Storage/SQLiteSessionStorage.h>


#include <Analytics/RuleBasedSummaryGenerator.h>
#include <Analytics/ActivitySummary.h>
#include <Monitor/Monitor.h>
#include <Window/Window.h>
#include <User/AuthContext.h>


#include <Backend/Backend.h>
#include <WebView/WebViewController.h>
#include <Backend/ActivityController.h>
#include <Backend/UserController.h>
#include <Backend/SessionController.h>
#include <Backend/AuthController.h>