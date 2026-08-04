#include <Activity/ActivityClassifier.h>
#include <Activity/Activity.h>
#include <Storage/IActivityStorage.h>
#include <Storage/ITagStorage.h>
#include <Tag/Tag.h>

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
	if (!m_storage.hasTag(ac.id, BuiltinTagId::Browser)) return;

	const auto& title = ac.window.title;
	if (title.find("GitHub") != std::string::npos)
	{
		m_storage.addTags(ac.id, { BuiltinTagId::Code });
	}
	else if (title.find("YouTube") != std::string::npos)
	{
		m_storage.addTags(ac.id, { BuiltinTagId::Video });
	}
}

void chronos::ActivityClassifier::classifyByProcess(Activity& ac)
{
	const auto& process = ac.window.processName;

	if (process == "explorer.exe")
	{
		m_storage.addTags(ac.id, { BuiltinTagId::FileManager });
	}
	else if (process == "chrome.exe" ||
		process == "firefox.exe")
	{
		m_storage.addTags(ac.id, { BuiltinTagId::Browser });
	}
	else if (process == "WindowsTerminal.exe")
	{
		m_storage.addTags(ac.id, { BuiltinTagId::Terminal });
	}
}

