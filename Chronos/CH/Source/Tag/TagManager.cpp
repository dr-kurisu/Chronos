#include <Tag/TagManager.h>
#include <Storage/ITagStorage.h>
#include <Tag/BuildinTags.h>

using namespace chronos;

TagManager::TagManager(const TagManagerDesc& desc):
	Base(desc.base), m_storage(desc.storage)
{
}

TagId TagManager::createTag(Tag& tag)
{
	if (m_currentUserId < 0)
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
	return m_storage.createTag(m_currentUserId, tag);
}

bool TagManager::ensureBuiltinTags()
{
	if (m_currentUserId < 0) 
	{
		ChronosLogWarning("Cannot create builtin tags without valid user.");
		return false;
	}
	return m_storage.ensureBuiltinTags(m_currentUserId);
}

bool TagManager::updateTag(const Tag&)
{
	return false;
}

bool TagManager::removeTag(const Tag&)
{
	return false;
}

void TagManager::setCurrentUserId(UserId id) { m_currentUserId = id; }

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
	auto tags = m_storage.getAllTags(m_currentUserId);
	for (auto& tag : tags)
	{
		m_tagMap.emplace(tag.id, std::move(tag));
	}
}
