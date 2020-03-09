// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHPROPERTYWIDGET_H
#define GRAPHPROPERTYWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class GraphModel;
class QBoxLayout;
class QSlider;
class JobManager;

namespace ModelView
{
class ItemsTreeView;
} // namespace ModelView

/*!
@class GraphPropertyWidget
@brief Shows model content in standard tree view.
*/

class GraphPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphPropertyWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);
    ~GraphPropertyWidget();

    void setModel(GraphModel* model);

private:
    void setup_slider();
    QSlider* m_slider;
    ModelView::ItemsTreeView* m_treeView;
    GraphModel* m_model;
    std::unique_ptr<JobManager> job_manager;
};

#endif // GRAPHPROPERTYWIDGET_H