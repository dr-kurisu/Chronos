#include <Activity/ActivityClassifier.h>
#include <Activity/Activity.h>

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
	// Only classify browser windows for now.
	if (ac.tags.find(ActivityTag::Browser) == ac.tags.end())
		return;

	const auto& title = ac.window.title;
	if (title.find("GitHub") != std::string::npos)
	{
		ac.tags.insert(ActivityTag::Code);
	}
	else if (title.find("YouTube") != std::string::npos)
	{
		ac.tags.insert(ActivityTag::Video);
	}
}

void chronos::ActivityClassifier::classifyByProcess(Activity& ac)
{
	const auto& process = ac.window.processName;

	if (process == "explorer.exe")
	{
		ac.tags.insert(ActivityTag::FileManager);
	}
	else if (process == "chrome.exe" ||
		process == "firefox.exe")
	{
		ac.tags.insert(ActivityTag::Browser);
	}
	else if (process == "WindowsTerminal.exe")
	{
		ac.tags.insert(ActivityTag::Terminal);
	}
}

