#include <Activity/ActivityClassifier.h>
#include <Activity/Activity.h>
#include <Storage/ITagStorage.h>
#include <Tag/BuildinTags.h>

chronos::ActivityClassifier::ActivityClassifier(const ActivityClassifierDesc& desc) :
	Base(desc.base), m_storage(desc.storage)
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
	if (!hasTag(ac.tags, ActivityTags::Browser)) return;

	const auto& title = ac.window.title;
	if (title.find("GitHub") != std::string::npos)
	{
		addTag(ac.tags, ActivityTags::Code);
	}
	else if (title.find("YouTube") != std::string::npos)
	{
		addTag(ac.tags, ActivityTags::Video);
	}
}

void chronos::ActivityClassifier::classifyByProcess(Activity& ac)
{
	const auto& process = ac.window.processName;

	if (process == "explorer.exe")
	{
		
		addTag(ac.tags, ActivityTags::FileManager);
	}
	else if (process == "chrome.exe" ||
		process == "firefox.exe")
	{
		addTag(ac.tags, ActivityTags::Browser);
	}
	else if (process == "WindowsTerminal.exe")
	{
		addTag(ac.tags, ActivityTags::Terminal);
	}
}

