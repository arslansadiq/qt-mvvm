// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemtags.h"
#include "sessionitemcontainer.h"
#include <stdexcept>

using namespace ModelView;

SessionItemTags::SessionItemTags() = default;

SessionItemTags::~SessionItemTags()
{
    for (auto tag : m_containers)
        delete tag;
}

void SessionItemTags::registerTag(TagInfo tagInfo, bool set_as_default)
{
    if (isTag(tagInfo.name()))
        throw std::runtime_error("SessionItemTags::registerTag() -> Error. Existing name '"
                                 + tagInfo.name() + "'");

    m_containers.push_back(new SessionItemContainer(tagInfo));
    if (set_as_default)
        m_default_tag = tagInfo.name();
}

//! Returns true if container with such name exists.

bool SessionItemTags::isTag(const std::string& name) const
{
    for (auto tag : m_containers)
        if (tag->name() == name)
            return true;
    return false;
}

//! Returns the name of the default tag.

std::string SessionItemTags::defaultTag() const
{
    return m_default_tag;
}

void SessionItemTags::setDefaultTag(const std::string& name)
{
    m_default_tag = name;
}

int SessionItemTags::itemCount(const std::string& tag_name) const
{
    return container(tag_name)->itemCount();
}

//! Inserts item in container with given tag name and at given index.
//! Returns true in the case of success. If tag name is empty, default tag will be used.

bool SessionItemTags::insertItem(SessionItem* item, const std::string& tag, int index)
{
    return container(tag)->insertItem(item, index);
}

//! Removes item at given index and for given tag, returns it to the user.

SessionItem* SessionItemTags::takeItem(const std::string& tag, int index)
{
    return container(tag)->takeItem(index);
}

//! Returns item at given index of given tag.

SessionItem* SessionItemTags::getItem(const std::string& tag, int index) const
{
    return container(tag)->itemAt(index);
}

//! Returns vector of items in the container with given name.
//! If tag name is empty, default tag will be used.

std::vector<SessionItem*> SessionItemTags::getItems(const std::string& tag) const
{
    return container(tag)->items();
}

std::vector<SessionItem*> SessionItemTags::allitems() const
{
    std::vector<SessionItem*> result;
    for (auto cont : m_containers) {
        auto container_items = cont->items();
        result.insert(result.end(), container_items.begin(), container_items.end());
    }

    return result;
}

//! Returns tag name and index of item in container.

std::pair<std::string, int> SessionItemTags::tagIndexOfItem(const SessionItem* item) const
{
    std::pair<std::string, int> result = std::make_pair("", -1);
    for (auto cont : m_containers) {
        int index = cont->indexOfItem(item);
        if (index != -1)
            return std::make_pair(cont->name(), index);
    }

    return result;
}

void SessionItemTags::itemDeleted(SessionItem* item)
{
    auto info = tagIndexOfItem(item);
    if (info.second != -1)
        container(info.first)->itemDeleted(item);
}

SessionItemTags::const_iterator SessionItemTags::begin() const
{
    return m_containers.begin();
}

SessionItemTags::const_iterator SessionItemTags::end() const
{
    return m_containers.end();
}

//! Returns true if given tag corresponds to registered single property tag.

bool SessionItemTags::isSinglePropertyTag(const std::string& tag) const
{
    auto cont = find_container(tag);
    return cont ? cont->tagInfo().isSinglePropertyTag() : false;
}

//! Returns container corresponding to given tag name. If name is empty,
//! default tag will be used. Exception is thrown if no such tag exists.

SessionItemContainer* SessionItemTags::container(const std::string& tag_name) const
{
    std::string tagName = tag_name.empty() ? defaultTag() : tag_name;
    auto container = find_container(tagName);
    if (!container)
        throw std::runtime_error("SessionItemTags::container() -> Error. No such container '"+tagName+"'");

    return container;
}

//! Returns container corresponding to given tag name.

SessionItemContainer* SessionItemTags::find_container(const std::string& tag_name) const
{
    for (auto cont : m_containers)
        if (cont->name() ==tag_name)
            return cont;

    return nullptr;
}
