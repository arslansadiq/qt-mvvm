// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "tagrow.h"

using namespace ModelView;

//! Returns TagRow corresponding to the append to tag_name.
//! If tag_name =="" the default name will be used in SessionItemTags context.

TagRow TagRow::append(const std::string& tag_name)
{
    return {tag_name, -1};
}

//! Returns TagRow corresponding to prepending to tag_name.
//! If tag_name =="" the default name will be used in SessionItemTags context.

TagRow TagRow::prepend(const std::string& tag_name)
{
    return {tag_name, 0};
}

bool TagRow::operator==(const TagRow& other) const
{
    return row == other.row && tag==other.tag;
}

bool TagRow::operator!=(const TagRow& other) const
{
    return !(*this == other);
}
