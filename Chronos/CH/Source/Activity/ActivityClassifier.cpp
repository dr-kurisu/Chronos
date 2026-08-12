#include <Activity/ActivityClassifier.h>
#include <Activity/Activity.h>
#include <Tag/Tag.h>
#include <ranges>

chronos::ActivityClassifier::ActivityClassifier(const ActivityClassifierDesc& desc) :
	Base(desc.base)
{
}

void chronos::ActivityClassifier::classify(Activity& ac)
{
	classifyByProcess(ac);
	classifyByWindows(ac);
}

void chronos::ActivityClassifier::classifyByWindows(Activity& ac)
{
	// Only classify browser windows for now. (without ac id here)
	if (!ac.hasTag(BuiltinTagId::Browser)) return;

	const auto& title = ac.window.title;
	if (title.find("GitHub") != std::string::npos)
	{
		ac.addTag(BuiltinTagId::Code);
	}
	else if (title.find("YouTube") != std::string::npos)
	{
		ac.addTag(BuiltinTagId::Video);
	}
}

void chronos::ActivityClassifier::classifyByProcess(Activity& ac)
{
	const auto& process = ac.window.processName;

	if (process == "explorer.exe")
	{
		ac.addTag(BuiltinTagId::FileManager);
	}
	else if (process == "chrome.exe" ||
		process == "firefox.exe")
	{
		ac.addTag(BuiltinTagId::Browser);
	}
	else if (process == "WindowsTerminal.exe")
	{
		ac.addTag(BuiltinTagId::Terminal);
	}
}

