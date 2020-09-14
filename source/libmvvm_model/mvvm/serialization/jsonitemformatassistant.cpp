// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <QStringList>
#include <mvvm/serialization/jsonitemformatassistant.h>

using namespace ModelView;

namespace
{
//! Returns list of keys which should be in QJsonObject to represent SessionItem.
QStringList expected_item_keys()
{
    QStringList result = QStringList() << JsonItemFormatAssistant::modelKey
                                       << JsonItemFormatAssistant::itemDataKey
                                       << JsonItemFormatAssistant::itemTagsKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemTags.

QStringList expected_tags_keys()
{
    QStringList result = QStringList() << JsonItemFormatAssistant::defaultTagKey
                                       << JsonItemFormatAssistant::containerKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = QStringList() << JsonItemFormatAssistant::tagInfoKey
                                       << JsonItemFormatAssistant::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionModel.

QStringList expected_sessionmodel_keys()
{
    QStringList result = QStringList() << JsonItemFormatAssistant::sessionModelKey
                                       << JsonItemFormatAssistant::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace

bool JsonItemFormatAssistant::isSessionItem(const QJsonObject& json) const
{
    static const QStringList expected = expected_item_keys();

    if (json.keys() != expected)
        return false;

    if (!json[itemDataKey].isArray())
        return false;

    if (!json[itemTagsKey].isObject())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemTags.

bool JsonItemFormatAssistant::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemContainer.

bool JsonItemFormatAssistant::isSessionItemContainer(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemcontainer_keys();

    if (json.keys() != expected)
        return false;

    if (!json[tagInfoKey].isObject())
        return false;

    if (!json[itemsKey].isArray())
        return false;

    return true;
}

bool JsonItemFormatAssistant::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_sessionmodel_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}