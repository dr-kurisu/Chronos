#pragma once
#include <Application/Application.h>
#include <Core/Logger.h>
#include <Storage/SQliteDatabase.h>
#include <Monitor/Monitor.h>

#include <User/UserManager.h>
#include <Tag/TagManager.h>
#include <Activity/ActivityManager.h>

#include <Storage/SQLiteActivityStorage.h>
#include <Storage/SQLiteTagStorage.h>
#include <Storage/SQLiteUserStorage.h>
#include <Storage/SQLitePlanStorage.h>
#include <Activity/Activity.h>

#include <Analytics/RuleBasedSummaryGenerator.h>
#include <Analytics/ActivitySummary.h>
#include <WebView/WebViewController.h>
#include <Window/Window.h>