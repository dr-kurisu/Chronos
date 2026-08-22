#include <Tag/TagManager.h>
#include <Storage/ITagStorage.h>
#include <Tag/BuildinTags.h>
#include <User/AuthContext.h>

using namespace chronos;

TagManager::TagManager(const TagManagerDesc& desc):
	Base(desc.base), m_storage(desc.storage), m_authContext(desc.authContext)
{
}

TagId TagManager::createTag(Tag& tag)
{
	auto userId = m_authContext.userId();
	if (!userId)
	{
		ChronosLogWarning("Cannot create tag without valid user.");
		return -1;
	}
	if (!tag.isValid())
	{
		ChronosLogWarning("Cannot create invalid tag.");
		return -1;
	}
	tag.builtin = false;
	return m_storage.createTag(*userId, tag);
}

bool TagManager::ensureBuiltinTags()
{
	auto userId = m_authContext.userId();
	if (!userId)
	{
		ChronosLogWarning("Cannot create builtin tags without valid user.");
		return false;
	}
	return m_storage.ensureBuiltinTags(*userId);
}

bool TagManager::updateTag(const Tag&)
{
	return false;
}

bool TagManager::removeTag(const Tag&)
{
	return false;
}

std::optional<Tag> TagManager::getTag(TagId id) const
{
	auto it = m_tagMap.find(id);
	if (it != m_tagMap.end())
	{
		return it->second;
	}

	return std::nullopt;
}

std::unordered_map<TagId, Tag> chronos::TagManager::getTagMap()
{
	return m_tagMap;
}

void TagManager::updateTagMap()
{
	m_tagMap.clear();
	auto userId = m_authContext.userId();
	if (!userId)
	{
		ChronosLogWarning("Fail to update TagMap with unauthoried userId.");
		return;
	}

	auto tags = m_storage.getAllTags(*userId);
	for (auto& tag : tags)
	{
		m_tagMap.emplace(tag.id, std::move(tag));
	}
}