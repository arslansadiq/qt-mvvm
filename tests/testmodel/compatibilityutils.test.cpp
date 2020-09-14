// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/compatibilityutils.h>

using namespace ModelView;

//! Test of CompatibilityUtilsTest.

class CompatibilityUtilsTest : public ::testing::Test
{
public:
    ~CompatibilityUtilsTest();
};

CompatibilityUtilsTest::~CompatibilityUtilsTest() = default;

//! Testing IsCompatibleSingleProperty.

TEST_F(CompatibilityUtilsTest, IsCompatibleSinglePropertyTag)
{
    const std::string name("tag");
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);

    // to be compatible, container should have PropertyItem in it already
    EXPECT_FALSE(Compatibility::IsCompatibleSinglePropertyTag(container, tag));

    EXPECT_TRUE(container.insertItem(new PropertyItem, 0));
    EXPECT_TRUE(Compatibility::IsCompatibleSinglePropertyTag(container, tag));
}

//! Testing IsCompatibleSingleProperty.

TEST_F(CompatibilityUtilsTest, IsCompatibleUniversalTag)
{
    const std::string name("tag");
    TagInfo tag = TagInfo::universalTag("layers");
    SessionItemContainer container(tag);

    // to be compatible, container should be empty
    EXPECT_TRUE(Compatibility::IsCompatibleUniversalTag(container, tag));

    EXPECT_TRUE(container.insertItem(new PropertyItem, 0));
    EXPECT_FALSE(Compatibility::IsCompatibleUniversalTag(container, tag));
}