// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SLDViewModel.h"

#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<HandleItem>();
    result->registerItem<SegmentItem>();
    result->registerItem<RoughnessViewItem>();
    return result;
}

QColor random_color()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}

} // namespace

SLDViewModel::SLDViewModel() : SessionModel("ViewItemsModel")
{
    setItemCatalogue(CreateItemCatalogue());
}

//! Add a handle view item
HandleItem* SLDViewModel::addHandle()
{
    auto handle = insertItem<HandleItem>();
    handle->setProperty(HandleItem::P_XPOS, 10.);
    handle->setProperty(HandleItem::P_XPOS, 10.);
    return handle;
}

//! Add a Segment view item
SegmentItem* SLDViewModel::addSegment(std::string layer_identifier_in)
{
    auto segment = insertItem<SegmentItem>();
    segment->setLayerIdentifier(layer_identifier_in);
    segment->setProperty(SegmentItem::P_X_POS, 0.);
    segment->setProperty(SegmentItem::P_Y_POS, 0.);
    segment->setProperty(SegmentItem::P_HEIGHT, 10.);
    segment->setProperty(SegmentItem::P_WIDTH, 150.);
    return segment;
}

//! Add a roughness view item
RoughnessViewItem* SLDViewModel::addRoughness(std::string layer_identifier_in)
{
    auto roughness = insertItem<RoughnessViewItem>();
    roughness->setLayerIdentifier(layer_identifier_in);
    roughness->setProperty(RoughnessViewItem::P_ROUGHNESS, 0.);
    return roughness;
}