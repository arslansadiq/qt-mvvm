// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/commands/removeitemcommand.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/itembackupstrategy.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const TagRow& tagrow);
} // namespace

struct RemoveItemCommand::RemoveItemCommandImpl {
    TagRow tagrow;
    result_t result;
    std::unique_ptr<ItemBackupStrategy> backup_strategy;
    Path item_path;
    RemoveItemCommandImpl(TagRow tagrow) : tagrow(std::move(tagrow)), result(false) {}
};

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, TagRow tagrow)
    : AbstractItemCommand(parent),
      p_impl(std::make_unique<RemoveItemCommandImpl>(std::move(tagrow)))
{
    setDescription(generate_description(p_impl->tagrow));
    p_impl->backup_strategy = parent->model()->itemBackupStrategy();
    p_impl->item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto reco_item = p_impl->backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), p_impl->tagrow);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    if (auto child = parent->takeItem(p_impl->tagrow); child) {
        p_impl->backup_strategy->saveItem(child);
        delete child;
        p_impl->result = true;
    } else {
        p_impl->result = false;
        setObsolete(true);
    }
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return p_impl->result;
}

namespace
{
std::string generate_description(const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
